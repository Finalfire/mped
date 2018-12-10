#include <iostream>
#include <string>

// Sequences and their representations
#include "sequence/AbstractSequence.h"
#include "sequence/DelimitedSequence.h"
#include "sequence/SimpleSequence.h"

#include "MatchingSchema.h"
#include "metric/EditDistance.h"
#include "metric/Jaro.h"

#include "heuristic/HillClimbing/HillClimbing.h"

void prova_seq() {
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
}

// compute edit over two strings
unsigned compute_edit(const std::string& a, const std::string& b) {

    std::vector<std::vector<unsigned>> matrix(a.size() + 1);
    for (auto& v: matrix)
        v = std::vector<unsigned>(b.size() + 1, 0);

    for (size_t i = 0; i < a.size()+1; i++) matrix[i][0] = i;
    for (size_t j = 0; j < b.size()+1; j++) matrix[0][j] = j;

    for (size_t i = 1; i < a.size() + 1; i++) {
        for (size_t j = 1; j < b.size() + 1; j++) {

            bool w = a[i-1] == b[j-1];

            matrix[i][j] = min(
                    matrix[i-1][j] + 1, // deletion
                    matrix[i][j-1] + 1, // insertion
                    // if in the matching schema there's a false, they match
                    matrix[i-1][j-1] + (1 * !w)
            );
        }
    }

    return matrix[a.size()][b.size()];
}

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);

    /*AbstractSequence s("ciao");
    std::cout << s.getBase() << std::endl;

    DelimitedSequence d("ciao bella uagliu");
    std::cout << d.getBase() << std::endl;

    MatchingSchema m(10, 10, 2, 2, true);
    m.print_matching_schema();*/

    /*prova_seq();
    token_seq();*/

    /*auto start = std::chrono::steady_clock::now();

    std::string a;
    std::string b;

    getline(std::cin, a);
    getline(std::cin, b);

    //EditDistance e(a.size(), b.size());
    std::cout << compute_edit(a, b) << std::endl;

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    std::cout << std::chrono::duration<double, std::milli> (diff).count() / (1000) << std::endl;*/



    HillClimbing h;
    std::cout << h.compute_heuristic()

    return 0;
}