#ifndef MPED_NLPMATCHINGSCHEMAFIXED_H
#define MPED_NLPMATCHINGSCHEMAFIXED_H

#include <iostream>
#include "utility/Utility.h"
#include "sequence/DelimitedSequence.h"
#include "../MatchingSchema.h"
#include "SparseDictionary.h"


class NLPMatchingSchemaFixed : public MatchingSchema {
public:

    size_t start_1;
    size_t start_2;

    SparseDictionary dict;

    NLPMatchingSchemaFixed(const size_t& sigma1_len, const size_t& sigma2_len, const size_t& p1, const size_t& p2,
                      const bool x, const SparseDictionary& dict1, size_t start_sigma_1, size_t start_sigma_2)
            : MatchingSchema(sigma1_len, sigma2_len, p1, p2, x),
              dict(dict1),
              start_1(start_sigma_1),
              start_2(start_sigma_2) {}

    void print_matching_schema(const DelimitedSequence& sigma1, const DelimitedSequence& sigma2) {
        std::cout << "\t";
        for (int j = 0; j < m; ++j)
            std::cout << sigma2.getSigma()[j] << "\t";
        std::cout << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << sigma1.getSigma()[i] << "\t";
            for (int j = 0; j < m; ++j)
                std::cout << ms[i][j] << "\t";
            std::cout << std::endl;
        }
    }

};


#endif //MPED_NLPMATCHINGSCHEMA_H
