#ifndef MPED_EVALUATIONFUNCTIONS_H
#define MPED_EVALUATIONFUNCTIONS_H

double compute_jaro(const std::vector<DelimitedSequence>& v, const std::vector<DelimitedSequence>& w,
                 const MatchingSchema &m, SparseDictionary& dict) {

    // compute Jaro for each pair
    std::vector<double> jaros;
    for (size_t i = 0; i < v.size(); i++)
        jaros.push_back(Jaro::compute(v[i], w[i], m, dict));

    double sum = std::accumulate(jaros.begin(), jaros.end(), 0.0);
    return sum / (double) jaros.size();
}

double compute_jaro(const std::vector<DelimitedSequence>& v, const std::vector<DelimitedSequence>& w, unsigned* sig1, unsigned* sig2,
                 const MatchingSchema &m, SparseDictionary& dict) {

    // compute Jaro for each pair
    std::vector<double> jaros;
    for (size_t i = 0; i < v.size(); i++)
        jaros.push_back(Jaro::compute(v[i], w[i], sig1, sig2, m, dict));

    double sum = std::accumulate(jaros.begin(), jaros.end(), 0.0);
    return sum / (double) jaros.size();
}

double compute_jaro_wavg(const std::vector<DelimitedSequence>& v, const std::vector<DelimitedSequence>& w, unsigned* sig1, unsigned* sig2,
                 const MatchingSchema &m, SparseDictionary& dict) {

    // compute Jaro for each pair
    std::vector<double> jaros;
    double weights = 0.0;
    size_t max_length = 0;

    for (size_t i = 0; i < v.size(); i++) {
        max_length = std::max(v[i].seq_len(), w[i].seq_len());
        jaros.push_back(Jaro::compute(v[i], w[i], sig1, sig2, m, dict) * (double) max_length);
        weights += (double) max_length;
    }

    double sum = std::accumulate(jaros.begin(), jaros.end(), 0.0);
    return sum / weights;
}

double compute_edit(const std::vector<DelimitedSequence>& v, const std::vector<DelimitedSequence>& w, unsigned* sig1, unsigned* sig2,
                    const MatchingSchema &m, SparseDictionary& dict) {

    // compute edit for each pair
    std::vector<double> edits;
    unsigned max_length = 0;

    for (size_t i = 0; i < v.size(); i++) {
        EditDistance e(v[i].seq_len(), w[i].seq_len());
        max_length = std::max(v[i].seq_len(), w[i].seq_len());
        unsigned d = e.compute_edit_enhanced(v[i], w[i], sig1, sig2, m, dict);
        edits.push_back(d / (double) max_length);
    }

    double sum = std::accumulate(edits.begin(), edits.end(), 0.0);
    return sum / (double) edits.size();
}

double compute_jaccard(const std::vector<DelimitedSequence>& v, const std::vector<DelimitedSequence>& w, unsigned* sig1, unsigned* sig2,
                 const MatchingSchema &m, SparseDictionary& dict) {

    // compute Jaro for each pair
    std::vector<double> jaccards;
    for (size_t i = 0; i < v.size(); i++)
        jaccards.push_back(Jaccard::compute(v[i], w[i], sig1, sig2, m, dict));

    double sum = std::accumulate(jaccards.begin(), jaccards.end(), 0.0);
    return sum / (double) jaccards.size();
}

double compute_jaccard_wavg(const std::vector<DelimitedSequence>& v, const std::vector<DelimitedSequence>& w, unsigned* sig1, unsigned* sig2,
                       const MatchingSchema &m, SparseDictionary& dict) {

    // compute Jaro for each pair
    std::vector<double> jaccards;
    double weights = 0.0;
    unsigned max_length = 0;

    for (size_t i = 0; i < v.size(); i++) {
        max_length = std::max(v[i].seq_len(), w[i].seq_len());
        jaccards.push_back(Jaccard::compute(v[i], w[i], sig1, sig2, m, dict));
        weights += (double) max_length;
    }

    double sum = std::accumulate(jaccards.begin(), jaccards.end(), 0.0);
    return sum / weights;
}



#endif //MPED_EVALUATEFUNCTIONS_H
