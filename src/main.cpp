#include <iostream>
#include "MPED.hpp"
#include "Sequence.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);

    Sequence a("aaaaabcdeeef");
    Sequence b("555553214446");

    std::cout << a.getSeq() << ' ' << a.getSigma() << std::endl;
    std::cout << b.getSeq() << ' ' << b.getSigma() << std::endl;

    for (auto x : a.getSeq_repr())
        std::cout << x << ' ';
    std::cout << std::endl;

    for (auto x : b.getSeq_repr())
        std::cout << x << ' ';
    std::cout << std::endl;

    return 0;
}