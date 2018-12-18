#include <iostream>
#include <string>

// Sequences and their representations
#include "sequence/AbstractSequence.h"
#include "sequence/DelimitedSequence.h"
#include "sequence/SimpleSequence.h"

#include "metric/EditDistance.h"
#include "heuristic/EvolutionStrategy/EvolutionStrategy.h"
#include "metric/Jaro.h"

#include "MPED.h"
#include "heuristic/EvolutionStrategy/Mutator/Shuffle.h"
#include "heuristic/EvolutionStrategy/Mutator/Inversion.h"
#include "heuristic/EvolutionStrategy/Mutator/Scramble.h"
#include "heuristic/EvolutionStrategy/Mutator/Swap2.h"
#include "heuristic/EvolutionStrategy/Mutator/Swap2_E.h"
#include "heuristic/EvolutionStrategy/Mutator/Swap2_Swap3.h"
#include "heuristic/EvolutionStrategy/Mutator/Swap3.h"
#include "heuristic/EvolutionStrategy/Mutator/Translocation.h"

#include "heuristic/HillClimbing/HillClimbing.h"


/*void prova_seq() {
    SimpleSequence a("aaaaabcdeeee");
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
    DelimitedSequence a("A B C D E");
    DelimitedSequence b("A X Y Z Q");

    std::cout << a.sigma_len() << ',' << b.sigma_len() << std::endl;

    MatchingSchema m(a.sigma_len(), b.sigma_len(), 1, 1, true);

    std::cout << Jaro::compute(a, b, m) << std::endl;
    std::cout << Jaro::jaro("MARTHA", "MARHTA") << std::endl;           // 0.94
    std::cout << Jaro::jaro("DIXON", "DICKSONX") << std::endl;          // 0.76
    std::cout << Jaro::jaro("JELLYFISH", "SMELLYFISH") << std::endl;    // 0.89

    EditDistance e(a.seq_len(), b.seq_len());
    std::cout << e.compute_edit(a, b, m) << std::endl;
}*/

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);

    // initialize the random number generator (with seed)
    std::srand(unsigned(std::time(NULL)));

    const size_t p1 = 1, p2 = 1;
    // exact solution: 24
    SimpleSequence s1("odkoodokogdkdkodgoddokkdkdgkogooddodgkkgkokdoooddg");
    SimpleSequence s2("ensnmememnssnesnseeesennnmmnmmsneeesnsnnsssememmnm");

    MatchingSchema* m = new MatchingSchema(s1.sigma_len(), s2.sigma_len(), p1, p2, true);
    EditDistance* metric= new EditDistance(s1.seq_len(), s2.seq_len(), m);

    unsigned maxgen=120, mu=30, lambda=120;
    EvolutionStrategy<Shuffle>* h_es = new EvolutionStrategy<Shuffle>(metric, maxgen, mu, lambda);
    HillClimbing* h_hc = new HillClimbing(metric);

    MPED mped(s1, s2, p1, p2, metric, h_es);

    std::cout << "DISTANCE: " << mped.compute_edit_heuristic() << std::endl;
    mped.setHeuristic(h_hc);
    std::cout << "DISTANCE: " << mped.compute_edit_heuristic() << std::endl;

    delete metric;
    delete m;

    return 0;
}