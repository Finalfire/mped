#ifndef MPED_JACCARD_H
#define MPED_JACCARD_H

#include <iostream>
#include <vector>
#include "DelimitedSequence.h"
#include "MatchingSchema.h"

class Jaccard {
public:
    static float compute(const DelimitedSequence& a, const DelimitedSequence& b, const MatchingSchema& m, SparseDictionary& dict) {
        std::vector<unsigned> sig1_index(a.sigma_len());
        for (unsigned i = 0; i < a.sigma_len(); i++)
            sig1_index[a.getSigma_repr()[i]] = i;

        std::vector<unsigned> sig2_index(b.sigma_len());
        for (unsigned i = 0; i < b.sigma_len(); i++)
            sig2_index[b.getSigma_repr()[i]] = i;

        // compute A = set(a)
        // compute B = set(b)
        // compute A^B = A intersection B

        // TODO: SICURO FUNZIONI?
        unsigned I = 0;
        for (size_t i = 0; i < a.getSigma_repr().size(); i++) {
            for (size_t j = i; j < b.getSigma_repr().size(); j++) {
                if (!m.ms[sig1_index[a.getSequence_repr()[i]]][sig2_index[b.getSequence_repr()[j]]] || dict.match(a.getSequence()[i], b.getSequence()[j]))
                    I++;
            }
        }

        // return |A^B| / |A| +  |B| - |A^B|
        return I / (a.getSigma_repr().size() + b.getSigma_repr().size() - I);
    }
};


#endif //MPED_JACCARD_H
