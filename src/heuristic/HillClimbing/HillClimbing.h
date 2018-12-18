#ifndef MPED_HILLCLIMBING_H
#define MPED_HILLCLIMBING_H

#include <numeric>
#include <vector>

#include "../Heuristic.h"
#include "../../sequence/AbstractSequence.h"

struct Permutation {
    std::vector<unsigned> perm;

    Permutation(size_t k) : perm(k) {
        std::iota(perm.begin(), perm.end(), 0);
    }
};

class HillClimbing : public Heuristic {
private:

    const unsigned MAX_ATTEMPTS = 1;

public:

    HillClimbing(Metric* m) : Heuristic(m) {};

    unsigned compute_heuristic(const AbstractSequence& a, const AbstractSequence& b) {
        Permutation p1(a.sigma_len());
        Permutation p2(b.sigma_len());
        unsigned d = this->metric->compute_distance_enhanced(a, b, p1.perm, p2.perm);

        unsigned min_dist = d;
        Permutation best_p1(a.sigma_len());
        Permutation best_p2(b.sigma_len());

        unsigned top_dist = min_dist;
        Permutation top_p1(a.sigma_len());
        Permutation top_p2(b.sigma_len());

        Permutation sigma1_o(a.sigma_len());
        Permutation sigma2_o(b.sigma_len());

        unsigned attempts = 0;
        unsigned depth = 0;
        bool improved = true;

        while (improved) {
            improved = false;

            for (size_t ip = 0; ip < a.sigma_len(); ip++) {
                for (size_t jp = ip; jp < a.sigma_len(); jp++) {

                    // here comes the swap for sigma1
                    std::copy(p1.perm.begin(), p1.perm.end(), sigma1_o.perm.begin());
                    std::swap(sigma1_o.perm[ip], sigma1_o.perm[jp]);

                    for (size_t ipp = 0; ipp < b.sigma_len(); ipp++) {
                        for (size_t jpp = ipp; jpp < b.sigma_len(); jpp++) {

                            std::copy(p2.perm.begin(), p2.perm.end(), sigma2_o.perm.begin());
                            std::swap(sigma2_o.perm[ipp], sigma2_o.perm[jpp]);

                            d = this->metric->compute_distance_enhanced(a, b, sigma1_o.perm, sigma2_o.perm);
                            if (d < min_dist) {
                                min_dist = d;
                                improved = true;

                                std::cout << "found: " << min_dist << std::endl;

                                std::copy(sigma1_o.perm.begin(), sigma1_o.perm.end(), best_p1.perm.begin());
                                std::copy(sigma2_o.perm.begin(), sigma2_o.perm.end(), best_p2.perm.begin());
                            }
                        }

                        std::copy(p2.perm.begin(), p2.perm.end(), sigma2_o.perm.begin());
                    }
                }
            }

            if (improved) {
                std::copy(best_p1.perm.begin(), best_p1.perm.end(), sigma1_o.perm.begin());
                std::copy(best_p2.perm.begin(), best_p2.perm.end(), sigma2_o.perm.begin());

                std::copy(best_p1.perm.begin(), best_p1.perm.end(), p1.perm.begin());
                std::copy(best_p2.perm.begin(), best_p2.perm.end(), p2.perm.begin());

                depth++;
            } else {
                if (min_dist < top_dist) {
                    top_dist = min_dist;

                    std::cout << "(top): " << top_dist << std::endl;

                    std::copy(best_p1.perm.begin(), best_p1.perm.end(), top_p1.perm.begin());
                    std::copy(best_p2.perm.begin(), best_p2.perm.end(), top_p2.perm.begin());

                    improved = true;
                    attempts = 0;
                    depth = 0;
                }

                if (attempts < this->MAX_ATTEMPTS) {
                    improved = true;
                    attempts++;

                    std::random_shuffle(p1.perm.begin(), p1.perm.end());
                    std::random_shuffle(p2.perm.begin(), p2.perm.end());

                    std::copy(p1.perm.begin(), p1.perm.end(), sigma1_o.perm.begin());
                    std::copy(p2.perm.begin(), p2.perm.end(), sigma2_o.perm.begin());

                    min_dist = this->metric->compute_distance_enhanced(a, b, p1.perm, p2.perm);
                } // an else branch here would be the last step before the termination;
            }
        }

        return top_dist;
    };
};


#endif //MPED_HILLCLIMBING_H
