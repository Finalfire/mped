//
// Created by lucac on 04/12/2018.
//

#ifndef MPED_HEURISTIC_H
#define MPED_HEURISTIC_H

#include"../metric/Metric.h"

class Heuristic {
protected:
    Metric* metric;

public:
    explicit Heuristic(Metric* m):metric(m){};

    virtual unsigned compute_heuristic(const AbstractSequence&, const AbstractSequence&) { return 0; };

};


#endif //MPED_HEURISTIC_H
