#include <chrono>
#include <iostream>
#include <string>

// MPED
#include "AbstractSequence.h"
#include "DelimitedSequence.h"
#include "SimpleSequence.h"
#include "EditDistance.h"

// NLP stuff
#include "NLP/SparseDictionary.h"
#include "NLP/NLPMatchingSchema.h"

// metric
#include "Jaccard.h"
#include "Jaro.h"

// heuristic
#include "HillClimbing.h"
#include "(mu+lambda)-ES.h"
#include "NLP/NLPMatchingSchema.h"

// utility stuff
#include "Utility.h"

void call_es(std::vector<DelimitedSequence>& v, std::vector<DelimitedSequence>& w, unsigned& p1, unsigned& p2,
             NLPMatchingSchema& m, SparseDictionary& dict, const unsigned& max_iteration, const unsigned& lambda, const unsigned& mu) {

    ES_mu_p_lambda es;

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    double jaro = es.evolutionStrategy_ensamble(v, w, p1, p2, m, dict, max_iteration, lambda, mu);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    // structure of the result is: p1, p2, max_iteration, lambda, mu, result, time (in sec)
    std::cout << p1 << '-' << p2 << ',' <<  max_iteration << ',' << lambda << ',' << mu << ','
              << jaro << ',' << time_span.count() << std::endl;
}

void single_child(DelimitedSequence& union_en, DelimitedSequence& union_it,
                  std::vector<DelimitedSequence>& en_sentences, std::vector<DelimitedSequence>& it_sentences,
                  SparseDictionary& dict) {

    /** Single children, pi = 2..10 **/

    unsigned mu = 20;
    unsigned lambda = 2;

    for (unsigned p = 2; p <= 10; p++) {
        // create a matching schema M on these words
        NLPMatchingSchema m(union_en.sigma_len(), union_it.sigma_len(), p, p, true, dict, union_en, union_it);

        call_es(en_sentences, it_sentences, p, p, m, dict, 1000, mu, lambda);
        call_es(en_sentences, it_sentences, p, p, m, dict, 2500, mu, lambda);
        call_es(en_sentences, it_sentences, p, p, m, dict, 5000, mu, lambda);
        call_es(en_sentences, it_sentences, p, p, m, dict, 7500, mu, lambda);
        call_es(en_sentences, it_sentences, p, p, m, dict, 10000, mu, lambda);
    }
}

void mu_lambda(DelimitedSequence& union_en, DelimitedSequence& union_it,
                  std::vector<DelimitedSequence>& en_sentences, std::vector<DelimitedSequence>& it_sentences,
                  SparseDictionary& dict) {

    /** Multiple children, pi = 2..10 **/

    for (unsigned p = 2; p <= 10; p++) {
        // create a matching schema M on these words
        NLPMatchingSchema m(union_en.sigma_len(), union_it.sigma_len(), p, p, true, dict, union_en, union_it);

        call_es(en_sentences, it_sentences, p, p, m, dict, 120, 30, 120);
        call_es(en_sentences, it_sentences, p, p, m, dict, 120, 30, 480);
    }

}

void main_flow() {

    // read dict
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    SparseDictionary dict("../one-to-one_pairs");
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "[read dict in " << time_span.count() << " seconds]" << std::endl;

    // tokenize all sentences in a row, in order to obtain the set of unique words
    DelimitedSequence union_en(readSequenceFromFile("../megafrase_en.txt"));
    DelimitedSequence union_it(readSequenceFromFile("../megafrase_it.txt"));

    // read all sequences in two different arrays
    std::vector<DelimitedSequence> en_sentences;
    std::vector<DelimitedSequence> it_sentences;
    std::fstream f;
    std::string temp;
    f.open("../frasi_eng_clean.txt", std::fstream::in);
    while (f.good()) { getline(f, temp); en_sentences.push_back(DelimitedSequence(temp, union_en)); }
    f.close();
    f.open("../frasi_ita_clean.txt", std::fstream::in);
    while (f.good()) { getline(f, temp); it_sentences.push_back(DelimitedSequence(temp, union_it)); }
    f.close();

    /** Experiments **/

    //single_child(union_en, union_it, en_sentences, it_sentences, dict);
    mu_lambda(union_en, union_it, en_sentences, it_sentences, dict);
}

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);

    main_flow();

    return 0;
}