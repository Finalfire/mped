//
// Created by lucac on 05/12/2018.
//

#ifndef MPED_INDIVIDUAL_H
#define MPED_INDIVIDUAL_H

#include "EvolutionStrategy.h"

class Individual
{
private:
    std::vector<unsigned> sigma1;
    std::vector<unsigned> sigma2;
    unsigned sigma1l;
    unsigned sigma2l;

    unsigned costValue;

public:
    enum optimization{
        maximize = 0,
        minimize = std::numeric_limits<unsigned int>::max()
    };

    // default constructor
    /*Individual(): sigma1l(0), sigma2l(0){
        costValue = 0;
    }*/

    Individual(Individual::optimization opt): sigma1l(0), sigma2l(0){
        costValue = opt;
    }

    Individual(Individual::optimization opt, const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2): sigma1(sig1), sigma2(sig2), sigma1l(sig1.size()), sigma2l(sig2.size()){
        costValue = opt;
    }

    /** getter & setter **/

    void setCostValue(unsigned c){
        costValue = c;
    }

    unsigned getCostValue() const {
        return costValue;
    }

     std::vector<unsigned>& getSigma1() {
        return sigma1;
    }

     std::vector<unsigned>& getSigma2() {
        return sigma2;
    }

    unsigned getSigma1l() const {
        return sigma1l;
    }

    unsigned getSigma2l() const {
        return sigma2l;
    }

    /** end - getter & setter **/

    bool operator<(const Individual& m) const
    {
        return this->getCostValue() < m.getCostValue();
    }
    /*

    ES_MatchingSchema(const ES_MatchingSchema& m) :
            sigma1l(m.sigma1l), sigma2l(m.sigma2l), costValue(m.costValue)
    {
        sigma1 = new unsigned[sigma1l];
        std::copy(m.sigma1, m.sigma1 + sigma1l, sigma1);

        sigma2 = new unsigned[sigma2l];
        std::copy(m.sigma2, m.sigma2 + sigma2l, sigma2);
    } */


/*
    void swap2(const unsigned n) const
    {
        //Perform multiple simple swap of two indices for every vector
        for (unsigned i = 0; i < n; ++i)
        {
            //first vector
            unsigned i_1 = rand() % sigma1l;
            unsigned i_2 = rand() % sigma1l;

            unsigned temp = sigma1[i_1];
            sigma1[i_1] = sigma1[i_2];
            sigma1[i_2] = temp;

            //second vector
            i_1 = rand() % sigma2l;
            i_2 = rand() % sigma2l;

            temp = sigma2[i_1];
            sigma2[i_1] = sigma2[i_2];
            sigma2[i_2] = temp;
        }
    }


    ES_MatchingSchema& operator=(const ES_MatchingSchema& m)
    {
        costValue = m.costValue;

        if (sigma1l != m.sigma1l)
        {
            sigma1l = m.sigma1l;
            if (sigma1 != NULL)
            {
                delete[] sigma1;
            }
            sigma1 = new unsigned[sigma1l];
        }
        std::copy(m.sigma1, m.sigma1 + sigma1l, sigma1);

        if (sigma2l != m.sigma2l)
        {
            sigma2l = m.sigma2l;
            if (sigma2 != NULL)
            {
                delete[] sigma2;
            }
            sigma2 = new unsigned[sigma2l];
        }
        std::copy(m.sigma2, m.sigma2 + sigma2l, sigma2);
        return *this;
    }

    bool operator==(const ES_MatchingSchema& m) const
    {
        if (costValue != m.costValue || sigma1l != m.sigma1l
            || sigma2l != m.sigma2l)
        {
            return false;
        }

        for (unsigned i = 0; i < sigma1l; ++i)
        {
            if (sigma1[i] != m.sigma1[i])
            {
                return false;
            }
        }

        for (unsigned i = 0; i < sigma2l; ++i)
        {
            if (sigma2[i] != m.sigma2[i])
            {
                return false;
            }
        }

        return true;
    }

    ~ES_MatchingSchema()
    {
        delete[] sigma1;
        delete[] sigma2;
    }

    void print() const
    {
        std::cout << "sigma1= ";
        for (unsigned i = 0; i < sigma1l; ++i)
        {
            std::cout << sigma1[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "sigma2= ";
        for (unsigned i = 0; i < sigma2l; ++i)
        {
            std::cout << sigma2[i] << " ";
        }
        std::cout << std::endl;
    }*/
};

#endif //MPED_INDIVIDUAL_H
