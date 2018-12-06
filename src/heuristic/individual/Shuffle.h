//
// Created by lucac on 06/12/2018.
//

#ifndef MPED_SHUFFLE_H
#define MPED_SHUFFLE_H

#include "Individual.h"

class Shuffle: public Individual{

public:
    explicit Shuffle(Individual::optimization opt):Individual(opt){};
    explicit Shuffle(Individual::optimization opt, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2): Individual(opt, sig1, sig2){}

    void mutate(){
        std::random_shuffle(sigma1.begin(), sigma1.end());
        std::random_shuffle(sigma2.begin(), sigma2.end());
    }

};

#endif //MPED_SHUFFLE_H
