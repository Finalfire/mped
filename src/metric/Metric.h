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
    bool used_diagonal_optimization = false;
    unsigned threshold = -1;

public:

    Metric(MatchingSchema* m) : matchingSchema(m) {}
    Metric(MatchingSchema* m, bool u_d_o, unsigned t) : matchingSchema(m), used_diagonal_optimization(u_d_o), threshold(t) {}
    virtual ~Metric() {}

    virtual unsigned compute_distance(const AbstractSequence& a, const AbstractSequence& b) { return 0; };
    virtual unsigned compute_distance_enhanced(const AbstractSequence& a, const AbstractSequence& b, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2) { return 0; };
    virtual unsigned compute_distance_enhanced_with_diagonal(const AbstractSequence& a, const AbstractSequence& b,const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2, size_t threshold) {return 0; };

    void setMatchingSchema(MatchingSchema* ms){
        this->matchingSchema = ms;
    }

    MatchingSchema* getMatchingSchema(){
        return this->matchingSchema;
    }

    bool isDiagonalOptimization(){
        return this->used_diagonal_optimization;
    }

    unsigned getThreshold(){
        return this->threshold;
    }

};

#endif //MPED_METRIC_H
