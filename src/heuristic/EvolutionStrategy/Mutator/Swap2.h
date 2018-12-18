//
// Created by lucac on 06/12/2018.
//

#ifndef MPED_SWAP2_H
#define MPED_SWAP2_H

#include "Swap2_Swap3.h"

class Swap2: public Swap2_Swap3{

public:
    //explicit Swap2(Individual::optimization opt):Swap2_Swap3(opt){};
    //explicit Swap2(Individual::optimization opt, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2): Swap2_Swap3(opt, sig1, sig2){}

    void mutate(Individual& individual){
        mutateSwap2(individual);
    }
};

#endif //MPED_SWAP2_H
