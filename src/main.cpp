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
#include "(mu+lambda)-ES.h"

int main() {
    std::ios_base::sync_with_stdio(false);

    SimpleSequence a("abc");
    SimpleSequence b("fed");
    EditDistance e1(a.seq_len(), b.seq_len());
    MatchingSchema m1(a.sigma_len(), b.sigma_len(), 1, 1, true);

    HillClimbing hc1;
    ES_mu_p_lambda es1;

    std::cout << hc1.hillclimbing(a, b, 1, 1, m1, e1) << std::endl;
    std::cout << es1.evolutionStrategy(a, b, 1, 1, m1, e1, 10, 4, 1) << std::endl;

    /*DelimitedSequence c("aaa bbbb cccc");
    DelimitedSequence d("ffffff eee dd");
    EditDistance e2(c.seq_len(), d.seq_len());
    MatchingSchema m2(c.sigma_len(), d.sigma_len(), 1, 1, true);
    HillClimbing hc2;
    std::cout << hc2.hillclimbing(c, d, 1, 1, m2, e2) << std::endl;
    ES_mu_p_lambda es1;
    std::cout << es1.evolutionStrategy(c, d, 1, 1, m2, e2, 10, 4, 1) << std::endl;

    //std::cout << e2.compute_edit(c, d, m2) << std::endl;

    DelimitedSequence e("A B C D E");
    DelimitedSequence f("A W X Y Z ");
    MatchingSchema m3(e.sigma_len(), f.sigma_len(), 1, 1, true);

    std::cout << Jaccard::compute(e, f, m3) << std::endl;
    std::cout << Jaro::compute(e, f, m3) << std::endl;*/

    return 0;
}