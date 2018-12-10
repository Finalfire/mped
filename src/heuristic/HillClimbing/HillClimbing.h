#ifndef MPED_HILLCLIMBING_H
#define MPED_HILLCLIMBING_H

#include "../Heuristic.h"
#include "../../sequence/AbstractSequence.h"

class HillClimbing : public Heuristic {

    unsigned compute_heuristic(const AbstractSequence&, const AbstractSequence&) {
        return 0;
    };
};


#endif //MPED_HILLCLIMBING_H
