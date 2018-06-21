#include <iostream>

#include "AbstractSequence.h"
#include "DelimitedSequence.h"
#include "SimpleSequence.h"
#include "EditDistance.h"

// metric
#include "Jaccard.h"
#include "Jaro.h"

// heuristic
#include "HillClimbing.h"


/*void prova_seq() {
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

    EditDistance e(a.seq_len(), b.seq_len());
    e.print_matrix();
    std::cout << e.compute_edit(a, b, m) << std::endl;
    e.print_matrix();
    std::cout << Jaccard::compute(a, b, m) << std::endl;

    std::cout << Jaro::compute(a, b, m) << std::endl;
    std::cout << Jaro::jaro("MARTHA", "MARHTA") << std::endl;           // 0.94
    std::cout << Jaro::jaro("DIXON", "DICKSONX") << std::endl;          // 0.76
    std::cout << Jaro::jaro("JELLYFISH", "SMELLYFISH") << std::endl;    // 0.89
}*/

int main() {
    std::ios_base::sync_with_stdio(false);

    SimpleSequence a("abc");
    SimpleSequence b("fed");
    EditDistance e1(a.seq_len(), b.seq_len());
    MatchingSchema m1(a.sigma_len(), b.sigma_len(), 1, 1, true);
    HillClimbing hc1;
    std::cout << e1.compute_edit(a, b, m1) << std::endl;
    std::cout << hc1.hillclimbing(a, b, 1, 1, m1, e1) << std::endl;

    DelimitedSequence c("aaa bbbb cccc");
    DelimitedSequence d("ffffff eee dd");
    EditDistance e2(c.seq_len(), d.seq_len());
    MatchingSchema m2(c.sigma_len(), d.sigma_len(), 1, 1, true);
    HillClimbing hc2;
    std::cout << hc2.hillclimbing(c, d, 1, 1, m2, e2) << std::endl;
    std::cout << e2.compute_edit(c, d, m2) << std::endl;

    DelimitedSequence e("A B C D E");
    DelimitedSequence f("A W X Y Z ");
    MatchingSchema m3(e.sigma_len(), f.sigma_len(), 1, 1, true);

    std::cout << Jaccard::compute(e, f, m3) << std::endl;
    std::cout << Jaro::compute(e, f, m3) << std::endl;

    return 0;
}