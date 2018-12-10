#ifndef EDITDISTANCE_H_
#define EDITDISTANCE_H_

#include <iostream>
#include "../MatchingSchema.h"
#include "../Matrix.h"
#include "../sequence/AbstractSequence.h"

class EditDistance {
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
    EditDistance(unsigned r, unsigned c) : n(r+1), m(c+1) {
        matrix = new Matrix<unsigned>(n, m, 0);
        clear();
    }

    ~EditDistance() { delete matrix; }

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
    unsigned compute_edit(const AbstractSequence& a, const AbstractSequence& b, const MatchingSchema& m) {
        for (size_t i = 1; i < a.seq_len() + 1; i++) {
            for (size_t j = 1; j < b.seq_len() + 1; j++) {
                (*matrix)(i, j) = min(
                        (*matrix)(i - 1, j) + 1, // deletion
                        (*matrix)(i, j - 1) + 1, // insertion
                        // if in the matching schema there's a false, they match
                        (*matrix)(i - 1, j - 1) +
                            (1 * m.ms[a.getSequence_repr()[i-1]][b.getSequence_repr()[j-1]])
                );
            }
        }

        return (*matrix)(a.seq_len(), b.seq_len());
    }

    // compute edit w/ permutations of sigma(s)
    unsigned compute_edit_enhanced(const AbstractSequence& a, const AbstractSequence& b,
                          unsigned* sig1, unsigned* sig2, const MatchingSchema& m) {

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
                        (1 * m.ms[sig1_index[a.getSequence_repr()[i - 1]]][sig2_index[b.getSequence_repr()[j - 1]]])
                );
            }
        }

        return (*matrix)(a.seq_len(), b.seq_len());
    }

    void print_matrix() {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++)
                std::cout << (*matrix)(i, j) << ' ';
            std::cout << std::endl;
        }
    }
};

#endif