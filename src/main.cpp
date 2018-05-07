#include <iostream>
#include "EditDistance.hpp"
#include "MatchingSchema.hpp"
#include "MPED.hpp"
#include "Sequence.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);

    Sequence a("aaaaabcdeeef");
    Sequence b("hhhhhijkpppp");

    /*std::cout << a.getSeq() << ' ' << a.getSigma() << std::endl;
    std::cout << b.getSeq() << ' ' << b.getSigma() << std::endl;

    for (auto x : a.getSeq_repr())
        std::cout << x << ' ';
    std::cout << std::endl;

    for (auto x : b.getSeq_repr())
        std::cout << x << ' ';
    std::cout << std::endl;*/

    EditDistance e(a.seq_len() + 1, b.seq_len() + 1);
    MatchingSchema m(a.sigma_len(), b.sigma_len(), 1, 1, true, false);
    m.set_general(false);

    unsigned edit_distance = e.compute_edit(a, b, m);

    std::cout << edit_distance << std::endl;

    return 0;
}