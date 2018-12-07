//
// Created by lucac on 07/12/2018.
//

#ifndef MPED_SWAP2_SWAP3_H
#define MPED_SWAP2_SWAP3_H

#include "Individual.h"

class Swap2_Swap3: public Individual{

protected:
    void mutateSwap2_sub(size_t index){
        // TODO verificare se i due indici sono uguali, allora non fare nulla (o trovare un ulteriore coppia)
        // TODO CREAREA UN NUOVO MUTATORE CHE CAMBIA SOLO UN TOT % RISPETTO ALLA SIZE DEL vettore SIGMA

        if (index == 1){
            //first vector
            unsigned index_1 = rand() % sigma1l;
            unsigned index_2 = rand() % sigma1l;
            unsigned temp = sigma1[index_1];
            sigma1[index_1] = sigma1[index_2];
            sigma1[index_2] = temp;
        } else if (index == 2){
            //second vector
            unsigned index_1 = rand() % sigma2l;
            unsigned index_2 = rand() % sigma2l;
            unsigned temp = sigma2[index_1];
            sigma2[index_1] = sigma2[index_2];
            sigma2[index_2] = temp;
        }

    }

    void mutateSwap2()
    {
        //Perform a single, simple swap of two indices for every vector

        // first vector
        mutateSwap2_sub(1);
        // second vector
        mutateSwap2_sub(2);
    }

    void mutateSwap3_sub(size_t index){
        if (index == 1){
            //first vector
            unsigned index_1 = rand() % sigma1l;
            unsigned index_2 = rand() % sigma1l;

            while (index_2 == index_1)
            {
                index_2 = rand() % sigma1l;
            }

            unsigned index_3 = rand() % sigma1l;

            while (index_3 == index_2 || index_3 == index_1)
            {
                index_3 = rand() % sigma1l;
            }

            unsigned temp1 = sigma1[index_1];
            unsigned temp2 = sigma1[index_2];
            unsigned temp3 = sigma1[index_3];
            sigma1[index_3] = temp1;
            sigma1[index_1] = temp2;
            sigma1[index_2] = temp3;
        } else if (index == 2){
            //second vector
            unsigned index_1 = rand() % sigma2l;
            unsigned index_2 = rand() % sigma2l;

            while (index_2 == index_1)
            {
                index_2 = rand() % sigma2l;
            }

            unsigned index_3 = rand() % sigma2l;

            while (index_3 == index_2 || index_3 == index_1)
            {
                index_3 = rand() % sigma2l;
            }

            unsigned temp1 = sigma2[index_1];
            unsigned temp2 = sigma2[index_2];
            unsigned temp3 = sigma2[index_3];
            sigma2[index_3] = temp1;
            sigma2[index_1] = temp2;
            sigma2[index_2] = temp3;
        }
    }

    void mutateSwap3()
    {
        // first vector
        mutateSwap3_sub(1);
        // second vector
        mutateSwap3_sub(2);
    }

public:
    explicit Swap2_Swap3(Individual::optimization opt):Individual(opt){};
    explicit Swap2_Swap3(Individual::optimization opt, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2): Individual(opt, sig1, sig2){}

    void mutate()
    {
        //first vector
        unsigned pickUpMutator = rand() % 2;
        if (pickUpMutator == 0)
            mutateSwap2_sub(1);
        else
            mutateSwap3_sub(1);

        //second vector
        pickUpMutator = rand() % 2;
        if (pickUpMutator == 0)
            mutateSwap2_sub(2);
        else
            mutateSwap3_sub(2);
    }
};

#endif //MPED_SWAP2_SWAP3_H
