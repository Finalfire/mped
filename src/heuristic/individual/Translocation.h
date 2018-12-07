//
// Created by lucac on 07/12/2018.
//

#ifndef MPED_TRANSLOCATION_H
#define MPED_TRANSLOCATION_H

#include "Individual.h"

class Translocation: public Individual{

public:
    explicit Translocation(Individual::optimization opt):Individual(opt){};
    explicit Translocation(Individual::optimization opt, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2): Individual(opt, sig1, sig2){}

    void mutate()
    {
        //first vector
        unsigned index_1 = rand() % sigma1l;
        unsigned index_2 = rand() % sigma1l;
        unsigned index_3 = rand() % sigma1l;

        while (index_2 < index_1)
        {
            index_2 = rand() % sigma1l;
        }

        while (index_3 < index_2)
        {
            index_3 = rand() % sigma1l;
        }

        std::rotate(&sigma1[index_1], &sigma1[index_2], &sigma1[index_3 + 1]);

        //second vector
        index_1 = rand() % sigma2l;
        index_2 = rand() % sigma2l;
        index_3 = rand() % sigma2l;

        while (index_2 < index_1)
        {
            index_2 = rand() % sigma2l;
        }

        while (index_3 < index_2)
        {
            index_3 = rand() % sigma2l;
        }

        std::rotate(&sigma2[index_1], &sigma2[index_2], &sigma2[index_3 + 1]);
    }
};

#endif //MPED_TRANSLOCATION_H
