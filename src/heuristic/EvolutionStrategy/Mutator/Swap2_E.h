//
// Created by lucac on 06/12/2018.
//

#ifndef MPED_SWAP2_E_H
#define MPED_SWAP2_E_H

#include "Mutator.h"

static unsigned* blocksig1 = NULL;
static unsigned* blocksig2 = NULL;

class Swap2_E: public Mutator{

public:

    //explicit Swap2_E(Individual::optimization opt):Individual(opt){};
    //explicit Swap2_E(Individual::optimization opt, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2): Individual(opt, sig1, sig2){}

    static void initializeBlocksSwap2E(const std::vector<unsigned>& sig, const size_t& p, const size_t& positionBlock)
    {
        unsigned* blocksig = new unsigned[sig.size()];
        if (positionBlock == 1)
            blocksig1 = blocksig;
        else if (positionBlock == 2)
            blocksig2 = blocksig;

        unsigned marker = 0;
        blocksig[0] = 0;
        for (unsigned i = 1; i < sig.size(); ++i)
        {
            if (i % p == 0)
            {
                ++marker;
            }
            blocksig[i] = marker;
        }
    }

    void mutate(Individual& individual)
    {
        unsigned sigma1l = individual.getSigma1l();
        unsigned sigma2l = individual.getSigma2l();

        //Perform a single, simple swap of two indices for every vector

        //first vector
        unsigned index_1 = rand() % sigma1l;
        unsigned index_2 = rand() % sigma1l;

        //if they are the same don't do anything. This for maintaining good mutator's properties
        if(index_2 != index_1)
        {
            while(blocksig1[index_1] == blocksig1[index_2])
            {
                index_2 = rand() % sigma1l;
            }
        }

        unsigned temp = individual.getSigma1()[index_1];
        individual.getSigma1()[index_1] = individual.getSigma1()[index_2];
        individual.getSigma1()[index_2] = temp;

        //second vector
        index_1 = rand() % sigma2l;
        index_2 = rand() % sigma2l;

        //if they are the same don't do anything. This for maintaining good mutator's properties
        if(index_2 != index_1)
        {
            while(blocksig2[index_1] == blocksig2[index_2])
            {
                index_2 = rand() % sigma2l;
            }
        }

        temp = individual.getSigma2()[index_1];
        individual.getSigma2()[index_1] = individual.getSigma2()[index_2];
        individual.getSigma2()[index_2] = temp;

    }


};

#endif //MPED_SWAP2_E_H
