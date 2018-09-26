#include <chrono>
#include <iostream>
#include <string>

// MPED
#include "sequence/AbstractSequence.h"
#include "sequence/DelimitedSequence.h"
#include "sequence/SimpleSequence.h"

// NLP stuff
#include "NLP/SparseDictionary.h"
#include "NLP/NLPMatchingSchema.h"
#include "NLP/MegaSigma.h"

// metric
#include "Jaro.h"

// heuristic
#include "(mu+lambda)-ES.h"
#include "NLP/NLPMatchingSchema.h"

// utility stuff
#include "utility/Utility.h"
#include "NLP/NLPMatchingSchemaFixed.h"

#include "weighted-matching/hungarian.h"
#include "weighted-matching/hungarian.cpp"


ES_MatchingSchema_Ensamble call_es_update(
        std::vector<DelimitedSequence>& v, std::vector<DelimitedSequence>& w,
        unsigned& p1, unsigned& p2, NLPMatchingSchemaFixed& m, SparseDictionary& dict,
        const unsigned& max_iteration, const unsigned& mu, const unsigned& lambda) {

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

    // cost value of best matching schema
    double result = 0.0;

    // an instance of evolution strategy (ES)
    ES_mu_p_lambda es;

    // if pi != 0 {compute with ES} else {compute only with dict}
    if (p1 != 0)
        result = es.evolutionStrategy_ensamble_ws(v, w, p1, p2, m, dict, max_iteration, mu, lambda);
    else
        result = EvaluationFunctions::compute_jaro_wavg_only_dict_ws(v, w, dict);

    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    // structure of the result is: pi, max_iteration, lambda, mu, result, time (in sec)
    std::cout << p1 << ',' << max_iteration << ',' << lambda << ',' << mu << ',' << result << ',' << time_span.count() << std::endl;

    return es.getBest_ms_jaro();
}

void compute_all_jaros(std::vector<DelimitedSequence>& en, std::vector<DelimitedSequence>& it, unsigned p1, unsigned p2,
                       const NLPMatchingSchemaFixed& m, SparseDictionary& dict, const ES_MatchingSchema_Ensamble& e) {

    // create the resulting matrix
    std::vector<std::vector<double>> result(en.size());
    for (size_t i = 0; i < result.size(); i++)
        result[i] = std::vector<double>(it.size());

    // output filename
    auto pi = std::to_string(p1);
    std::string file_name("results_");
    file_name += pi + ".txt";
    std::cout << "[writing " << file_name << "]" << std::endl;

    std::fstream f(file_name, std::fstream::out);

    // compute
    for (size_t i = 0; i < en.size(); i++) {
        for (size_t j = i; j < it.size(); j++) {
            if (p1 != 0)
                result[i][j] = Jaro::compute_ws(en[i], it[j], e.sigma1, e.sigma2, m, dict);
            else
                result[i][j] = Jaro::compute_only_dict(en[i], it[j], dict);
            result[j][i] = result[i][j];
        }
    }

    // write into file
    for (size_t i = 0; i < en.size(); i++) {
        for (size_t j = 0; j < it.size(); j++)
            f << result[i][j] << ' ';
        f << '\n';
    }

    f.close();

}

void single_child_update(std::vector<DelimitedSequence>& en_sentences, std::vector<DelimitedSequence>& it_sentences,
                         const MegaSigma& mega_en, const MegaSigma& mega_it, SparseDictionary& dict) {
    unsigned mu = 1;
    unsigned lambda = 1;
    unsigned p = 0;
    unsigned max_generation = 5;

    // create a matching schema M on these words
    NLPMatchingSchemaFixed m(mega_en.getSymbols_sigma().size(), mega_it.getSymbols_sigma().size(), p, p, true, dict, mega_en.getStart_sigma(), mega_it.getStart_sigma());

    // compute the es and save the best matching schema e
    ES_MatchingSchema_Ensamble e = call_es_update(en_sentences, it_sentences, p, p, m, dict, max_generation, mu, lambda);

    // compute the e-parameterized jaro for each pair of sentences
    //compute_all_jaros(en_sentences, it_sentences, p, p, m, dict, e);
}

void main_flow_update() {
    // read dict
    SparseDictionary dict("../one-to-one_pairs");
    std::cout << "[read dict]" << std::endl;

    // tokenize all sentences in a row, in order to obtain the set of unique words
    DelimitedSequence union_en(readSequenceFromFile("../advanced_experiments/megafrase_en_clean.txt"));
    DelimitedSequence union_it(readSequenceFromFile("../advanced_experiments/megafrase_it_clean.txt"));
    std::cout << "[read megafrasi]" << std::endl;

    // create megasigma
    MegaSigma mega_en(dict.getEn_lemma(), union_en.getBase());
    MegaSigma mega_it(dict.getIt_lemma(), union_it.getBase());
    std::cout << "[created both megasigma]" << std::endl;

    // read all sequences in two different arrays
    std::vector<DelimitedSequence> en_sentences;
    std::vector<DelimitedSequence> it_sentences;
    std::fstream f;
    std::string temp;

    f.open("../advanced_experiments/sentences_en_clean.txt", std::fstream::in);
    while (f.good()) {
        getline(f, temp);
        en_sentences.push_back(DelimitedSequence(temp, mega_en));
    }
    f.close();
    std::cout << "[read " << en_sentences.size() << " en sentences]" << std::endl;

    f.open("../advanced_experiments/sentences_it_clean.txt", std::fstream::in);
    while (f.good()) {
        getline(f, temp);
        it_sentences.push_back(DelimitedSequence(temp, mega_it));
    }
    f.close();
    std::cout << "[read " << it_sentences.size() << " it sentences]" << std::endl;

    /** Experiments **/
    std::cout << "Pi,N,Mu,Lambda,Result,Time(sec)" << std::endl;
    single_child_update(en_sentences, it_sentences, mega_en, mega_it, dict);
}

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    main_flow_update();

    return 0;
}