#ifndef MPED_PERMUTATION_H
#define MPED_PERMUTATION_H

class Permutation {
private:
    std::vector<unsigned> sigma_1;
    std::vector<unsigned> sigma_2;

public:

    Permutation(const unsigned& n, const unsigned& m) {
        sigma_1 = std::vector<unsigned>(n);
        sigma_2 = std::vector<unsigned>(m);

        std::iota(sigma_1.begin(), sigma_1.end(), 0);
        std::iota(sigma_2.begin(), sigma_2.end(), 0);
    }
};

#endif //MPED_PERMUTATION_H
