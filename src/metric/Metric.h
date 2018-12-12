//
// Created by lucac on 04/12/2018.
//

#ifndef MPED_METRIC_H
#define MPED_METRIC_H

#include <iostream>


#include "../MatchingSchema.h"
#include "../Matrix.h"
#include "../sequence/AbstractSequence.h"

class Metric{
protected:

    MatchingSchema* matchingSchema;

public:

    Metric(MatchingSchema* m) : matchingSchema(m) {}
    virtual ~Metric() {}

    virtual unsigned compute_distance(const AbstractSequence& a, const AbstractSequence& b) { return 0; };
    virtual unsigned compute_distance_enhanced(const AbstractSequence& a, const AbstractSequence& b, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2) { return 0; };

    void setMatchingSchema(MatchingSchema* ms){
        this->matchingSchema = ms;
    }

    MatchingSchema* getMatchingSchema(){
        return this->matchingSchema;
    }
};

#endif //MPED_METRIC_H
