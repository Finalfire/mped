//
// Created by lucac on 06/12/2018.
//

#ifndef MPED_SHUFFLE_H
#define MPED_SHUFFLE_H

#include "Mutator.h"

class Shuffle: public Mutator{

public:
    //explicit Shuffle(Individual::optimization opt):Individual(opt){};
    //explicit Shuffle(Individual::optimization opt, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2): Individual(opt, sig1, sig2){}

    void mutate(Individual& individual)
    {
        unsigned sigma1l = individual.getSigma1l();
        unsigned sigma2l = individual.getSigma2l();

        //std::random_shuffle(sigma1->begin(), sigma1->end());
        //std::random_shuffle(sigma2->begin(), sigma2->end());

        std::random_shuffle(individual.getSigma1().begin(), individual.getSigma1().end());
        std::random_shuffle(individual.getSigma2().begin(), individual.getSigma2().end());

    }

};

#endif //MPED_SHUFFLE_H
