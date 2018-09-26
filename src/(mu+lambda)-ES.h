#ifndef MPED_MU_LAMBDA_ES_H
#define MPED_MU_LAMBDA_ES_H

#include <algorithm>
#include <numeric>
#include <vector>
#include "MatchingSchema.h"
#include "sequence/AbstractSequence.h"
#include "ES_MatchingSchema.h"
#include "EvaluationFunctions.h"
#include "NLP/NLPMatchingSchemaFixed.h"


class ES_mu_p_lambda {
private:
    ES_MatchingSchema_Ensamble best_ms_jaro;

public:
    ES_mu_p_lambda() = default;

    // da usare con Jaro e Jaccard (risultato 1 = simile)
    double evolutionStrategy_ensamble_ws(const std::vector<DelimitedSequence>& v, const std::vector<DelimitedSequence>& w, const unsigned &p1, const unsigned &p2,
                                      const NLPMatchingSchemaFixed& m, SparseDictionary& dict, const unsigned& max_generations,
                                      const unsigned& mu, const unsigned& lambda) {

        //Initialize stuff for the mutator swap2-E
        const unsigned* const blocksig1 = initializeBlocksSwap2E(v[0].getSigma_repr(), p1);
        const unsigned* const blocksig2 = initializeBlocksSwap2E(w[0].getSigma_repr(), p2);

        ES_MatchingSchema_Ensamble startingMS(v[0].getSigma_repr(), w[0].getSigma_repr());
        ES_MatchingSchema_Ensamble best;
        best.costValue = std::numeric_limits<unsigned int>::max();

        std::chrono::steady_clock::time_point t1;
        std::chrono::steady_clock::time_point t2;
        std::chrono::duration<double> time_span;

        //Generate mu random individuals
        ES_MatchingSchema_Ensamble* parents = new ES_MatchingSchema_Ensamble[mu + lambda];
        for (unsigned i = 0; i < mu; i++) {

            startingMS.shuffle();
            t1 = std::chrono::steady_clock::now();
            startingMS.costValue = (-1) * EvaluationFunctions::compute_jaro_wavg_ws(v, w, startingMS.sigma1, startingMS.sigma2, m, dict);
            t2 = std::chrono::steady_clock::now();

            time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

            std::cout << "ES >> generated parent " << i << " in " << time_span.count() << " seconds" << std::endl;
            parents[i] = startingMS;
        }

        const unsigned last = mu - 1;

        //Select the worst parent in the pool
        double worstParentCostValue = parents[0].costValue;
        for (unsigned i=1; i < mu; i++)
            if (parents[i].costValue > worstParentCostValue)
                worstParentCostValue = parents[i].costValue;

        unsigned generation = 0;
        while (generation < max_generations) {
            std::cout << "ES >> generation " << generation << std::endl;

            unsigned childrenInPool = 0;

            //Generate lambda children. Only mutation, no recombination
            for (unsigned i = 0; i < lambda; i++) {
                //Choose random parent
                const unsigned p = rand() % mu;

                //Produce child, in the case parents=1 just clone
                ES_MatchingSchema_Ensamble child = parents[p];

                //mutate child
                child.swap2_enhanced(blocksig1, blocksig2);

                const double newDistance = (-1) * EvaluationFunctions::compute_jaro_wavg_ws(v, w, child.sigma1, child.sigma2, m, dict);

                if (newDistance < child.costValue) {
                    //The child is better than the worst parent,
                    child.costValue = newDistance;

                    //so he is added to the pool
                    parents[mu + childrenInPool] = child;
                    childrenInPool++;
                }
            }

            //sorting for selecting the best mu individuals and at the same time get the worst parent
            std::sort(parents, parents + mu + childrenInPool);
            worstParentCostValue = parents[last].costValue;

            //Make a random_shuffle for keeping high entropy
            std::random_shuffle(parents, parents+mu);

            generation++;
        }

        std::sort(parents, parents+mu+lambda);
        best = parents[0];

        this->best_ms_jaro = best;

        delete[] blocksig1;
        delete[] blocksig2;
        delete[] parents;

        return best.costValue;
    }

    const ES_MatchingSchema_Ensamble &getBest_ms_jaro() const {
        return best_ms_jaro;
    }
};

#endif
