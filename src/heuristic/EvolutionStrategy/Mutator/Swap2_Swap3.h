//
// Created by lucac on 07/12/2018.
//

#ifndef MPED_SWAP2_SWAP3_H
#define MPED_SWAP2_SWAP3_H

#include "Mutator.h"

class Swap2_Swap3: public Mutator{

protected:
    void mutateSwap2_sub(Individual& individual, size_t index){
        // TODO verificare se i due indici sono uguali, allora non fare nulla (o trovare un ulteriore coppia)
        // TODO CREAREA UN NUOVO MUTATORE CHE CAMBIA SOLO UN TOT % RISPETTO ALLA SIZE DEL vettore SIGMA

        unsigned sigma1l = individual.getSigma1l();
        unsigned sigma2l = individual.getSigma2l();

        if (index == 1){
            //first vector
            unsigned index_1 = rand() % sigma1l;
            unsigned index_2 = rand() % sigma1l;
            unsigned temp = individual.getSigma1()[index_1];
            individual.getSigma1()[index_1] = individual.getSigma1()[index_2];
            individual.getSigma1()[index_2] = temp;
        } else if (index == 2){
            //second vector
            unsigned index_1 = rand() % sigma2l;
            unsigned index_2 = rand() % sigma2l;
            unsigned temp = individual.getSigma2()[index_1];
            individual.getSigma2()[index_1] = individual.getSigma2()[index_2];
            individual.getSigma2()[index_2] = temp;
        }

    }

    void mutateSwap2(Individual& individual)
    {
        //Perform a single, simple swap of two indices for every vector

        // first vector
        mutateSwap2_sub(individual, 1);
        // second vector
        mutateSwap2_sub(individual, 2);
    }

    void mutateSwap3_sub(Individual& individual, size_t index){

        unsigned sigma1l = individual.getSigma1l();
        unsigned sigma2l = individual.getSigma2l();

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

            unsigned temp1 = individual.getSigma1()[index_1];
            unsigned temp2 = individual.getSigma1()[index_2];
            unsigned temp3 = individual.getSigma1()[index_3];
            individual.getSigma1()[index_3] = temp1;
            individual.getSigma1()[index_1] = temp2;
            individual.getSigma1()[index_2] = temp3;
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

            unsigned temp1 = individual.getSigma2()[index_1];
            unsigned temp2 = individual.getSigma2()[index_2];
            unsigned temp3 = individual.getSigma2()[index_3];
            individual.getSigma2()[index_3] = temp1;
            individual.getSigma2()[index_1] = temp2;
            individual.getSigma2()[index_2] = temp3;
        }
    }

    void mutateSwap3(Individual& individual)
    {
        // first vector
        mutateSwap3_sub(individual, 1);
        // second vector
        mutateSwap3_sub(individual, 2);
    }

public:
    //explicit Swap2_Swap3(Individual::optimization opt):Individual(opt){};
    //explicit Swap2_Swap3(Individual::optimization opt, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2): Individual(opt, sig1, sig2){}

    void mutate(Individual& individual)
    {
        //first vector
        unsigned pickUpMutator = rand() % 2;
        if (pickUpMutator == 0)
            mutateSwap2_sub(individual, 1);
        else
            mutateSwap3_sub(individual, 1);

        //second vector
        pickUpMutator = rand() % 2;
        if (pickUpMutator == 0)
            mutateSwap2_sub(individual, 2);
        else
            mutateSwap3_sub(individual, 2);
    }
};

#endif //MPED_SWAP2_SWAP3_H
