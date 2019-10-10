#ifndef EDITDISTANCE_H_
#define EDITDISTANCE_H_

#include "Metric.h"
#include <cstdlib>

class EditDistance: public Metric{
private:
    unsigned n;
    unsigned m;
    Matrix<unsigned>* matrix;


    void clear() {
        // setup the matrix here
        for (size_t i = 0; i < n; i++) (*matrix)(i,0) = i;
        for (size_t j = 0; j < m; j++) (*matrix)(0,j) = j;
    }

public:

    EditDistance(unsigned r, unsigned c, MatchingSchema* ms) : Metric(ms), n(r+1), m(c+1) {
        matrix = new Matrix<unsigned>(n, m , 0);
        clear();
    };

    // used to diagonal optimization
    EditDistance(unsigned r, unsigned c, MatchingSchema* ms, bool u_d_o, unsigned t) : Metric(ms, u_d_o, t), n(r+1), m(c+1) {
        matrix = new Matrix<unsigned>(n, m , 0);
        clear();
    };
    ~EditDistance(){delete matrix;}

    // compute edit over two strings
    unsigned compute_edit(const std::string& a, const std::string& b) {
        for (size_t i = 1; i < a.size() + 1; i++) {
            for (size_t j = 1; j < b.size() + 1; j++) {

                bool w = a[i-1] == b[j-1];

                (*matrix)(i, j) = min(
                        (*matrix)(i - 1, j) + 1, // deletion
                        (*matrix)(i, j - 1) + 1, // insertion
                        // if in the matching schema there's a false, they match
                        (*matrix)(i - 1, j - 1) + (1 * !w)
                );
            }
        }

        return (*matrix)(a.size(), b.size());
    }

    // compute edit normal w/o any permutation of sigma(s)
    unsigned compute_distance(const AbstractSequence& a, const AbstractSequence& b) {
        for (size_t i = 1; i < a.seq_len() + 1; i++) {
            for (size_t j = 1; j < b.seq_len() + 1; j++) {
                (*matrix)(i, j) = min(
                        (*matrix)(i - 1, j) + 1, // deletion
                        (*matrix)(i, j - 1) + 1, // insertion
                        // if in the matching schema there's a false, they match
                        (*matrix)(i - 1, j - 1) +
                            (1 * matchingSchema->ms[a.getSequence_repr()[i-1]][b.getSequence_repr()[j-1]])
                );
            }
        }

        return (*matrix)(a.seq_len(), b.seq_len());
    }

    // compute edit w/ permutations of sigma(s)
    unsigned compute_distance_enhanced(const AbstractSequence& a, const AbstractSequence& b,
                          const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2) {

        std::vector<unsigned> sig1_index(a.sigma_len());
        for (unsigned i = 0; i < a.sigma_len(); i++)
            sig1_index[sig1[i]] = i;

        std::vector<unsigned> sig2_index(b.sigma_len());
        for (unsigned i = 0; i < b.sigma_len(); i++)
            sig2_index[sig2[i]] = i;

        for (size_t i = 1; i < a.seq_len() + 1; i++) {
            for (size_t j = 1; j < b.seq_len() + 1; j++) {
                (*matrix)(i, j) = min(
                        (*matrix)(i - 1, j) + 1, // deletion
                        (*matrix)(i, j - 1) + 1, // insertion
                        // if in the matching schema there's a false, they match
                        (*matrix)(i - 1, j - 1) +
                        (1 * matchingSchema->ms[sig1_index[a.getSequence_repr()[i - 1]]][sig2_index[b.getSequence_repr()[j - 1]]])
                );
            }
        }

        return (*matrix)(a.seq_len(), b.seq_len());
    }


    // tale funzione permette di calcolare la distanza se risulta essere inferiore al threshold
    // riducendo il tempo di esecuzione a O(k*m), calcolando solo una striscia di diagonali 2k+1.
    //

    //int edit_distance_matching_schema_enhanced_with_diagonal(const std::vector<unsigned>& s1, const std::vector<unsigned>& s2, int s1l, int s2l,
    //                                                         unsigned* sig1, unsigned* sig2, const size_t& sig1l, const size_t& sig2l, const matching_schema<bool>& m, int threshold){

    unsigned compute_distance_enhanced_with_diagonal(const AbstractSequence& a, const AbstractSequence& b,
                                const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2, size_t threshold){

        int MAX = std::numeric_limits<int>::max();

        if (std::abs((long)(a.seq_len()-b.seq_len()))>=threshold || threshold<0)
            return -1;

        // TODO: this must be fixed
        // uso la dimensione piu piccola tra le due s1l e s2l (m,n)
        /*if (s1l>s2l){
            unsigned *temp=s1;		// temp è un array come s1
            unsigned templ=s1l;		// lunghezza di s1
            s1=s2;					// s1 contiene s2 adesso
            s2=temp;				// s2 contiene s1 adesso
            s1l=s2l;				// lunghezza di s1 è quella di s2
            s2l=templ;				// lunghezza di s2 è quella di s1 (temp
        }*/

        // Permutation index
        std::vector<unsigned> sig1_index(a.sigma_len());
        for (unsigned i = 0; i < a.sigma_len(); i++)
            sig1_index[sig1[i]] = i;

        std::vector<unsigned> sig2_index(b.sigma_len());
        for (unsigned i = 0; i < b.sigma_len(); i++)
            sig2_index[sig2[i]] = i;


        // uso due righe e non la matrice completa
        unsigned* row=new unsigned[a.seq_len()+1];
        unsigned* col=new unsigned[a.seq_len()+1];

        int boundary=std::min(a.seq_len(), threshold)+1;
        for (int i=0; i<boundary; i++)
            row[i]=i;

        // fill array
        for (int i=boundary; i<a.seq_len()+1; i++)
            row[i]=MAX;
        for (int i=0; i<a.seq_len()+1; i++)
            col[i]=MAX;

        // iteration
        for (int j=1; j<=b.seq_len(); j++){
            unsigned charS2=b.getSequence_repr()[j-1];
            col[0]=j;

            int min=std::max(1, (int)(j-threshold));
            int max=(j>MAX-threshold)?a.seq_len():std::min(a.seq_len(), j+threshold);

            if (min>max){
                return -1;
            }

            if (min>1){
                col[min-1]=MAX;
            }

            for (int i=min; i<=max; i++){
                if (!matchingSchema->ms[sig1_index[a.getSequence_repr()[i-1]]][sig2_index[charS2]])
                    col[i]=row[i-1];
                else
                    col[i]=1+std::min(std::min(col[i-1],row[i]),row[i-1]);
            }

            //row=col;
            for (int c=0; c<a.seq_len()+1; c++)
                row[c]=col[c];
        }

        unsigned valuefinal=row[a.seq_len()];

        delete[] row;
        delete[] col;

        if (valuefinal<threshold)
            return valuefinal;

        return -1;
    }

    void print_matrix() {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++)
                std::cout << (*matrix)(i, j) << ',';
            std::cout << std::endl;
        }
    }

    unsigned getN(){return n;}
    unsigned getM(){return m;}

    Matrix<unsigned>* getMatrix(){return matrix;}
};

#endif