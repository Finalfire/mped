//
// Created by lucac on 17/12/2018.
//

#ifndef MPED_MUTATOR_H
#define MPED_MUTATOR_H

#include "../EvolutionStrategy.h"

class Mutator{


public:

    virtual void mutate(Individual& individual) {}

};

#endif //MPED_MUTATOR_H
