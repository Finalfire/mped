#ifndef EDITDISTANCE_H_
#define EDITDISTANCE_H_

#include <iostream>
#include "MatchingSchema.h"
#include "Matrix.h"
#include "Sequence.hpp"
#include "DelimitedSequence.h"

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

    unsigned compute_edit(const Sequence& a, const Sequence& b, const MatchingSchema& m) {

        auto* sig1_index = new unsigned[a.sigma_len()];
        for (unsigned i = 0; i < a.sigma_len(); ++i)
            sig1_index[a.getSigma_repr()[i]] = i;

        auto* sig2_index = new unsigned[b.sigma_len()];
        for (unsigned i = 0; i < b.sigma_len(); ++i)
            sig2_index[b.getSigma_repr()[i]] = i;

        for (size_t i = 1; i < a.seq_len() + 1; i++) {
            for (size_t j = 1; j < b.seq_len() + 1; j++) {
                (*matrix)(i, j) = min(
                        (*matrix)(i - 1, j) + 1, // deletion
                        (*matrix)(i, j - 1) + 1, // insertion
                        // if in the matching schema there's a false, they match
                        (*matrix)(i - 1, j - 1) +
                            (1 * m.ms
                                 [sig1_index[a.getSeq_repr()[i - 1]]]
                                 [sig2_index[b.getSeq_repr()[j - 1]]])
                );
            }
        }

        delete[] sig1_index;
        delete[] sig2_index;

        return (*matrix)(a.seq_len(), b.seq_len());
    }

    unsigned compute_edit(const DelimitedSequence& a, const DelimitedSequence& b, const MatchingSchema& m) {

        unsigned* sig1_index = new unsigned[a.sigma_len()];
        for (unsigned i = 0; i < a.sigma_len(); ++i)
            sig1_index[a.getSigma_repr()[i]] = i;

        unsigned* sig2_index = new unsigned[b.sigma_len()];
        for (unsigned i = 0; i < b.sigma_len(); ++i)
            sig2_index[b.getSigma_repr()[i]] = i;

        for (size_t i = 1; i < a.seq_len() + 1; i++) {
            for (size_t j = 1; j < b.seq_len() + 1; j++) {
                (*matrix)(i, j) = min(
                        (*matrix)(i-1, j) + 1, // deletion
                        (*matrix)(i, j-1) + 1, // insertion
                        // if in the matching schema there's a false, they match
                        (*matrix)(i-1, j-1) +
                            (1 * m.ms
                                 [sig1_index[a.getSeq_repr()[i - 1]]]
                                 [sig2_index[b.getSeq_repr()[j - 1]]])
                );
            }
        }

        delete[] sig1_index;
        delete[] sig2_index;

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