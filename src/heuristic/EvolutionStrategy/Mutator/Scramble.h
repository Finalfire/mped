//
// Created by lucac on 07/12/2018.
//

#ifndef MPED_SCRAMBLE_H
#define MPED_SCRAMBLE_H

#include "Mutator.h"

class Scramble: public Mutator{

public:
    //explicit Scramble(Individual::optimization opt):Individual(opt){};
    //explicit Scramble(Individual::optimization opt, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2): Individual(opt, sig1, sig2){}

    void mutate(Individual& individual)
    {
        unsigned sigma1l = individual.getSigma1l();
        unsigned sigma2l = individual.getSigma2l();

        //first vector
        unsigned index_1 = rand() % sigma1l;
        unsigned index_2 = rand() % sigma1l;

        while (index_2 < index_1)
        {
            index_2 = rand() % sigma1l;
        }

        //std::random_shuffle(&((*sigma1)[index_1]), &((*sigma1)[index_2 + 1]));
        std::random_shuffle(individual.getSigma1().begin()+index_1, individual.getSigma1().begin()+index_2+1);

        //second vector
        index_1 = rand() % sigma2l;
        index_2 = rand() % sigma2l;

        while (index_2 < index_1)
        {
            index_2 = rand() % sigma2l;
        }

        //std::random_shuffle(&((*sigma2)[index_1]), &((*sigma2)[index_2 + 1]));
        std::random_shuffle(individual.getSigma2().begin()+index_1, individual.getSigma2().begin()+index_2+1);
    }
};

#endif //MPED_SCRAMBLE_H
