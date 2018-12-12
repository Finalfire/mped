#ifndef MPED_PERMUTATION_H
#define MPED_PERMUTATION_H

#include <numeric>
#include <tuple>
#include <vector>

class Permutation {
private:
    std::vector<unsigned> sigma_1;
    std::vector<unsigned> sigma_2;

public:

    typedef std::tuple<std::vector<unsigned>, std::vector<unsigned>> perm;

    Permutation(const unsigned& n, const unsigned& m) {
        sigma_1 = std::vector<unsigned>(n);
        sigma_2 = std::vector<unsigned>(m);

        std::iota(sigma_1.begin(), sigma_1.end(), 0);
        std::iota(sigma_2.begin(), sigma_2.end(), 0);
    }

    perm getPermutation() const {
        return std::make_tuple(sigma_1, sigma_2);
    }

    const std::vector<unsigned>& getSigma_1() const { return sigma_1; }
    const std::vector<unsigned>& getSigma_2() const { return sigma_2; }
};

#endif //MPED_PERMUTATION_H
