//
// Created by lucacinelli on 04/12/2018.
//

// MPED(a, b, EditDistance, Heuristics);

#ifndef MPED_MPED_H
#define MPED_MPED_H

#include<iostream>
#include<vector>

#include"metric/Metric.h"
#include"heuristic/Heuristic.h"

class MPED{

private:
    void initMatchingSchema(const size_t sig1l, const size_t sig2l, const size_t p1, const size_t p2){
        matchingSchema = new MatchingSchema(s1.sigma_len(), s2.sigma_len(), p1, p2, true);
        metric->setMatchingSchema(matchingSchema);
    }

protected:
    AbstractSequence s1;
    AbstractSequence s2;
    Metric* metric;
    Heuristic* heuristic;
    MatchingSchema* matchingSchema;

public:

    explicit MPED(const AbstractSequence& s1, const AbstractSequence& s2, const size_t p1, const size_t p2, Metric* m, Heuristic* h):s1(s1), s2(s2), metric(m), heuristic(h){
        initMatchingSchema(s1.sigma_len(), s2.sigma_len(), p1, p2);
    }


    void updateParameters(const AbstractSequence& s1, const AbstractSequence& s2, const size_t p1, const size_t p2){
        this->s1 = s1;
        this->s2 = s2;
        initMatchingSchema(s1.sigma_len(), s2.sigma_len(), p1, p2);
    }

    void updateStrings(const AbstractSequence& s1, const AbstractSequence& s2){
        this->s1 = s1;
        this->s2 = s2;
        initMatchingSchema(s1.sigma_len(), s2.sigma_len(), 1, 1);
    }

    void setHeuristic(Heuristic* h) {
        this->heuristic = h;
    }

    unsigned compute_edit(){
        return metric->compute_distance(s1, s2);
    }

    unsigned compute_edit_heuristic(){
        return heuristic->compute_heuristic(s1, s2);
    }
};

#endif //MPED_MPED_H
