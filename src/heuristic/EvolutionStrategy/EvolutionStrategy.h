//
// Created by lucacinelli on 04/12/2018.
//

#ifndef EVOLUTIONSTRATEGY_H
#define EVOLUTIONSTRATEGY_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <queue>
#include <string>
#include <type_traits>

#include "../Heuristic.h"
#include "Individual.h"
#include "Mutator/Mutator.h"
#include "Mutator/Swap2_E.h"


#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)

//Template that represents the kind of individual to instantiate
template <class T>
class EvolutionStrategy: public Heuristic {
protected:
	const size_t max_generations;
	const size_t mu;
	const size_t lambda;
	Mutator* mutator;

private:
	/// <summary>To generate MU random individuals (to initialize the pool of parents from initial parent)
	void GenerateParents(const AbstractSequence& a1, const AbstractSequence& a2, std::vector<Individual>& parents, Individual firstIndividual){
		for (size_t i = 1; i < mu; i++){
			mutator->mutate(firstIndividual);
			firstIndividual.setCostValue(metric->compute_distance_enhanced(a1, a2, firstIndividual.getSigma1(), firstIndividual.getSigma2())); // TODO compute enhanced

			parents[i]=firstIndividual;
		}

		/* PRINT PERMUTATION OF POOL PARENTS
		std::cout<<std::endl;
		for (size_t i = 0; i<mu; i++){
			std::cout<<std::to_string(i) <<std::endl;
			for (size_t j = 0; j<parents[i].getSigma1().size(); j++) {
				std::cout<<parents[i].getSigma1()[j]<< " ";
			}
			std::cout<<std::endl;
		}*/

	}

	/// <summary>To select the worst parent cost value within pool parents
	unsigned getWorstParentCostValue(std::vector<Individual>& parents, bool minimize){
		unsigned worstParentCostValue = parents[0].getCostValue();

		if (minimize) {
			for (size_t i = 1; i < mu; i++) {
				if (parents[i].getCostValue() > worstParentCostValue)
					worstParentCostValue = parents[i].getCostValue();
			}

			return worstParentCostValue;
		} else {
			for (size_t i = 1; i < mu; i++) {
				if (parents[i].getCostValue() < worstParentCostValue)
					worstParentCostValue = parents[i].getCostValue();
			}

			return worstParentCostValue;
		}

		return worstParentCostValue;
	}

public:

	EvolutionStrategy(Metric* m, const size_t& max_gen, const size_t& mu, const size_t& lambda):Heuristic(m), max_generations(max_gen), mu(mu), lambda(lambda){
		mutator = new T();
	};
	~EvolutionStrategy(){}

	unsigned compute_heuristic(const AbstractSequence& a1, const AbstractSequence& a2) {
		std::vector<unsigned> s1 = a1.getSequence_repr(), s2 = a2.getSequence_repr();
		size_t sLen1 = s1.size(), sLen2 = s2.size();
		std::vector<unsigned> sig1 = a1.getSigma_repr(), sig2 = a2.getSigma_repr();
		size_t sigLen1 = sig1.size(), sigLen2 = sig2.size();
		MatchingSchema* matchingSchema = metric->getMatchingSchema();


		//Check if the individual are Swap2-E, so that we initialize stuff for the mutuator (swap2 specific for Edit Distance)
		if (std::is_same<T, Swap2_E>::value){
			Swap2_E::initializeBlocksSwap2E(sig1, matchingSchema->p1, 1);
			Swap2_E::initializeBlocksSwap2E(sig2, matchingSchema->p2, 2);
		}

		Individual firstIndividual(Individual::optimization::minimize, sig1, sig2);
		Individual bestIndividual(Individual::optimization::minimize);

		//Generate mu random individuals
		std::vector<Individual> parents(mu+lambda, Individual(Individual::optimization::minimize));
		parents[0] = firstIndividual;
		GenerateParents(a1, a2, parents, firstIndividual);

		//Get the worst cost value within pool
		unsigned worstParentCostValue = getWorstParentCostValue(parents, true);


		// START ALGORITHM
		unsigned generation = 0;
		while (generation <= max_generations) {
			unsigned childrenInPool = 0;

			//Generate lambda children. Only mutation, no recombination
			for (unsigned i = 0; i < lambda; i++) {
				//Choose random parent
				const unsigned p = rand() % mu;

				//Create a new child from a random parent chosen from pool parents
				Individual child = parents[p];

				//Mutate child
				mutator->mutate(child);
				//child.swap2_enhanced(blocksig1, blocksig2);

				//Compute edit distance on this child sigma permutation, and update cost value of child
				const unsigned distanceChild = metric->compute_distance_enhanced(a1, a2, child.getSigma1(), child.getSigma2());

				// TODO inserire la mia con la distanza.
				/*const int newDistance =
						e.edit_distance_matching_schema_enhanced_with_diagonal(s1,
																			   s2, s1l, s2l, child.sigma1, child.sigma2,
																			   sig1l,
																			   sig2l, m, worstParentCostValue);*/

				if (distanceChild != -1) {

					// TODO check if the parents is better than the worst parent
					//The child is better than the worst parent,
					child.setCostValue(distanceChild);

					parents[mu + childrenInPool] = child;
					childrenInPool++;
				}
			}

			//sorting for selecting the best mu individuals and at the same time get the worst parent
			std::sort(parents.begin(), parents.end());

			// PRINT POOL PARENTS
			std::cout<<"List of Parents:"<<std::endl;
			for (size_t k = 0; k < parents.size(); k++){
				std::cout<<parents[k].getCostValue() << " ";
			}

			worstParentCostValue = parents[mu + childrenInPool].getCostValue();

			//Make a random_shuffle for keeping high entropy
			std::random_shuffle(parents.begin(), parents.begin() + mu);

			generation++;
		}

		std::sort(parents.begin(), parents.end());
		bestIndividual = parents[0];
		//delete[] blocksig1;
		//delete[] blocksig2;

		return bestIndividual.getCostValue();
	}

};

#endif //EVOLUTIONSTRATEGY_H
