//
// Created by lucac on 07/12/2018.
//

#ifndef MPED_INVERSION_H
#define MPED_INVERSION_H

#include "Individual.h"

class Inversion: public Individual{

public:
    explicit Inversion(Individual::optimization opt):Individual(opt){};
    explicit Inversion(Individual::optimization opt, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2): Individual(opt, sig1, sig2){}

    void mutate()
    {
        //first vector
        unsigned index_1 = rand() % sigma1l;
        unsigned index_2 = rand() % sigma1l;

        while (index_2 < index_1)
        {
            index_2 = rand() % sigma1l;
        }

        std::reverse(&sigma1[index_1], &sigma1[index_2 + 1]);

        //second vector
        index_1 = rand() % sigma2l;
        index_2 = rand() % sigma2l;

        while (index_2 < index_1)
        {
            index_2 = rand() % sigma2l;
        }

        std::reverse(&sigma2[index_1], &sigma2[index_2 + 1]);
    }
};

#endif //MPED_INVERSION_H
