#include <iostream>
#include <string>

// Sequences and their representations
#include "sequence/AbstractSequence.h"
#include "sequence/DelimitedSequence.h"
#include "sequence/SimpleSequence.h"

#include "metric/EditDistance.h"
#include "heuristic/EvolutionStrategy/EvolutionStrategy.h"
#include "heuristic/EvolutionStrategy/EvolutionStrategyThread2.h"
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

unsigned exact(const AbstractSequence& a, const AbstractSequence& b) {

    MatchingSchema m(a.sigma_len(), b.sigma_len(), 1, 1, true);
    EditDistance edit(a.seq_len(), b.seq_len(), &m);

    std::vector<unsigned> sig1(a.sigma_len()), sig2(b.sigma_len());
    std::iota(sig1.begin(), sig1.end(), 0);
    std::iota(sig2.begin(), sig2.end(), 0);

    unsigned dist = INT_MAX;
    unsigned d = dist;

    do {
        d = edit.compute_distance_enhanced(a, b, sig1, sig2);

        if (d < dist)
            dist = d;
    } while(std::next_permutation(sig1.begin(), sig1.end()));

    return dist;
}

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);

    // initialize the random number generator (with seed)
    std::srand(unsigned(std::time(NULL)));

    const size_t p1 = 1, p2 = 1;
    // exact solution: 24
    //SimpleSequence s1("odkoodokogdkdkodgoddokkdkdgkogooddodgkkgkokdoooddg");
    //SimpleSequence s2("ensnmememnssnesnseeesennnmmnmmsneeesnsnnsssememmnm");

    // ( case 14_2000)
    SimpleSequence s1("kkkpauiupdoippuqdfippokziopodfzakuukfououzkudaokkqaafiuzpzfkkfozqzopaqppaoppqfuaqpauppiozifkzpikukpaqqiauzkpkzdkoukoqpkuoduuddafzupqfiqdaqadooizkpouuafkzapokpdoqkpuqfakaakfupudquqpdkdzduapizddoakdifkqqkaquqdooiiuqpouqqfqzffofupdpffzkipfiiofkdupdzdqudoqfipakqdfpoqfpziqakpqdqkipuiukzpoioudpppddudoiqppopqokkfikfpakozfuufiduuouqquzkdpodqdaizpozfoqfkziouzfqokpfaqopfiuiqaiozziffpdpffudoqkfappzkouakkikqpozuzpdqupkozfkakikqfiiiuofoaoaqkfqifpffiudaiakipfpiuuipoiikfouquaqzupidaauozzoazufzduifpuoadfuqpzziz");
    SimpleSequence s2("rkkrartayatrdlylygykjtkjrlarrjtkdddyyrydjyyrdkgzjklazdzydykkazgargallkdlrzkklrdtaddyyltkajlatatlktdkdjddtjaddlyrdzldkyrrrjrkzzdjdrydjrrjgztyrjjrjalgazgjtjyyztrrrayljggkjggtrzkltdztgyaalztaydaatzrzallylkktjdrlljadltdkgjdtlyjgjzddljlgytzlyyldtyyjjazzdydddlatllrzykggztydkyzkrgykzdtkatrktgdarazgddydrjdgtzagykryjrrgdkdzzdjrtzrktdytzltrlkgatdaaggygjlzdygtkrjgyjyakggjkzakyalaldgtjakjggzajljrkdkgkryygglggdlddzrtdkdtyggjddryzyrytayrdrlrzrazallylyadkkldltlklzdttydjjkgzgtggajkaatadjadjlzjzygyalaggykyjgagal");

    MatchingSchema* m = new MatchingSchema(s1.sigma_len(), s2.sigma_len(), p1, p2, true);
    EditDistance* metric= new EditDistance(s1.seq_len(), s2.seq_len(), m);

    unsigned maxgen=120, mu=30, lambda=139;
    EvolutionStrategy<Swap2_E>* h_es = new EvolutionStrategy<Swap2_E>(metric, maxgen, mu, lambda);
    EvolutionStrategyThread2<Swap2_E>* h_es_thread = new EvolutionStrategyThread2<Swap2_E>(metric, maxgen, mu, lambda);
    //HillClimbing* h_hc = new HillClimbing(metric);

    MPED mped(s1, s2, p1, p2, metric, h_es_thread);

    std::cout << "DISTANCE: " << mped.compute_edit_heuristic() << std::endl;
    //mped.setHeuristic(h_es);
    //std::cout << "DISTANCE: " << mped.compute_edit_heuristic() << std::endl;
    //mped.setHeuristic(h_hc);
    //std::cout << "DISTANCE: " << mped.compute_edit_heuristic() << std::endl;

    /*std::vector<unsigned> v1 = {2, 4, 5, 7, 1, 9, 3, 0, 8, 6};
    std::vector<unsigned> v2 = {8, 4, 6, 2, 5, 9, 1, 3, 7, 0 };

    EditDistance eFra(500, 500, m);
    std::cout<<"CI "<<eFra.compute_distance_enhanced(s1, s2, v1, v2)<<std::endl;*/

    delete metric;
    delete m;

    return 0;
}