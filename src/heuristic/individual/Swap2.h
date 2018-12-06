//
// Created by lucac on 06/12/2018.
//

#ifndef MPED_SWAP2_H
#define MPED_SWAP2_H

#include "Individual.h"

class Swap2: public Individual{

public:
    explicit Swap2(Individual::optimization opt):Individual(opt){};
    explicit Swap2(Individual::optimization opt, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2): Individual(opt, sig1, sig2){}

    void mutate()
    {
        //Perform a single, simple swap of two indices for every vector

        //first vector
        unsigned index_1 = rand() % sigma1l;
        unsigned index_2 = rand() % sigma1l;

        // TODO verificare se i due indici sono uguali, allora non fare nulla (o trovare un ulteriore coppia)
        // TODO CREAREA UN NUOVO MUTATORE CHE CAMBIA SOLO UN TOT % RISPETTO ALLA SIZE DEL vettore SIGMA

        unsigned temp = sigma1[index_1];
        sigma1[index_1] = sigma1[index_2];
        sigma1[index_2] = temp;

        //second vector
        index_1 = rand() % sigma2l;
        index_2 = rand() % sigma2l;

        temp = sigma2[index_1];
        sigma2[index_1] = sigma2[index_2];
        sigma2[index_2] = temp;
    }
};

#endif //MPED_SWAP2_H
