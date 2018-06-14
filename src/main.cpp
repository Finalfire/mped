#include <iostream>
#include "EditDistance.h"
#include "MatchingSchema.h"
#include "MPED.hpp"
#include "Sequence.hpp"
#include "DelimitedSequence.h"

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

    EditDistance e(a.seq_len() + 1, b.seq_len() + 1);
    MatchingSchema m(a.sigma_len(), b.sigma_len(), 1, 1, true);

    unsigned edit_distance = e.compute_edit(a, b, m);

    std::cout << edit_distance << std::endl;
}

void token_seq() {
    DelimitedSequence a("aaa bbb ccc ddd eee fff", " ");
    DelimitedSequence b("aaa bbb ccc ddd eee fff", " ");

    EditDistance e(a.seq_len()+1, b.seq_len()+1);
    MatchingSchema m(a.sigma_len(), b.sigma_len(), 1, 1, true);

    unsigned edit_distance = e.compute_edit(a, b, m);
    std::cout << edit_distance << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    token_seq();

    return 0;
}