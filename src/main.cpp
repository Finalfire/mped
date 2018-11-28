#include <iostream>
#include <string>

// Sequences and their representations
#include "sequence/AbstractSequence.h"
#include "sequence/DelimitedSequence.h"
#include "sequence/SimpleSequence.h"


#include "MatchingSchema.h"
#include "metric/EditDistance.h"
#include "metric/Jaro.h"

void prova_seq() {
    SimpleSequence a("aaaaabcdeeef");
    SimpleSequence b("hhhhhijkpppp");

    std::cout << a.getSequence() << ' ' << a.getSigma() << std::endl;
    std::cout << b.getSequence() << ' ' << b.getSigma() << std::endl;

    for (auto x : a.getSequence_repr())
        std::cout << x << ' ';
    std::cout << std::endl;

    for (auto x : b.getSequence_repr())
        std::cout << x << ' ';
    std::cout << std::endl;

    EditDistance e(a.seq_len(), b.seq_len());
    MatchingSchema m(a.sigma_len(), b.sigma_len(), 1, 1, true);

    unsigned edit_distance = e.compute_edit(a, b, m);
    std::cout << edit_distance << std::endl;
}

void token_seq() {
    DelimitedSequence a("A B C D E", " ");
    DelimitedSequence b("A X Y Z Q", " ");

    std::cout << a.sigma_len() << ',' << b.sigma_len() << std::endl;

    MatchingSchema m(a.sigma_len(), b.sigma_len(), 1, 1, true);

    std::cout << Jaro::compute(a, b, m) << std::endl;
    std::cout << Jaro::jaro("MARTHA", "MARHTA") << std::endl;           // 0.94
    std::cout << Jaro::jaro("DIXON", "DICKSONX") << std::endl;          // 0.76
    std::cout << Jaro::jaro("JELLYFISH", "SMELLYFISH") << std::endl;    // 0.89
}

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);

    //prova_seq();
    //token_seq();

    AbstractSequence s("ciao");
    std::cout << s.getBase() << std::endl;

    DelimitedSequence d("ciao bella uagliu");
    std::cout << d.getBase() << std::endl;

    return 0;
}