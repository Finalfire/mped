#include <iostream>
#include "EditDistance.h"
#include "MatchingSchema.h"
#include "MPED.hpp"
#include "Sequence.hpp"
#include "DelimitedSequence.h"
#include "Jaccard.h"
#include "Jaro.h"

void prova_seq() {
    Sequence a("aaaaabcdeeef");
    Sequence b("hhhhhijkpppp");

    std::cout << a.getSeq() << ' ' << a.getSigma() << std::endl;
    std::cout << b.getSeq() << ' ' << b.getSigma() << std::endl;

    for (auto x : a.getSeq_repr())
        std::cout << x << ' ';
    std::cout << std::endl;

    for (auto x : b.getSeq_repr())
        std::cout << x << ' ';
    std::cout << std::endl;

    EditDistance e(a.seq_len(), b.seq_len());
    MatchingSchema m(a.sigma_len(), b.sigma_len(), 1, 1, true);

    //unsigned edit_distance = e.compute_edit(a, b, m);
    //std::cout << edit_distance << std::endl;
}

void token_seq() {
    DelimitedSequence a("A B C D E", " ");
    DelimitedSequence b("A X Y Z Q", " ");

    std::cout << a.sigma_len() << ',' << b.sigma_len() << std::endl;

    MatchingSchema m(a.sigma_len(), b.sigma_len(), 1, 1, true);

    /*EditDistance e(a.seq_len(), b.seq_len());
    e.print_matrix();
    std::cout << e.compute_edit(a, b, m) << std::endl;
    e.print_matrix();

    std::cout << Jaccard::compute(a, b, m) << std::endl;*/

    std::cout << Jaro::compute(a, b, m) << std::endl;
    std::cout << Jaro::jaro("MARTHA", "MARHTA") << std::endl;           // 0.94
    std::cout << Jaro::jaro("DIXON", "DICKSONX") << std::endl;          // 0.76
    std::cout << Jaro::jaro("JELLYFISH", "SMELLYFISH") << std::endl;    // 0.89
}

int main() {
    std::ios_base::sync_with_stdio(false);

    token_seq();

    return 0;
}