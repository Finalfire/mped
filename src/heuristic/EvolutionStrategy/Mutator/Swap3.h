//
// Created by lucac on 07/12/2018.
//

#ifndef MPED_SWAP3_H
#define MPED_SWAP3_H

#include "Swap2_Swap3.h"

class Swap3: public Swap2_Swap3{

public:
    //explicit Swap3(Individual::optimization opt):Swap2_Swap3(opt){};
    //explicit Swap3(Individual::optimization opt, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2): Swap2_Swap3(opt, sig1, sig2){}

    void mutate(Individual& individual)
    {
        mutateSwap3(individual);
    }
};

#endif //MPED_SWAP3_H
