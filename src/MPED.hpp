#ifndef MPED_H
#define MPED_H

#include "EditDistance.h"
#include "Sequence.hpp"

class MPED {
private:
    unsigned p1;
    unsigned p2;

    Sequence a;
    Sequence b;

    EditDistance* e;
    MatchingSchema* m;

public:
    MPED() = default;

    MPED(Sequence s1, Sequence s2) : a(s1), b(s2) {};




};

#endif