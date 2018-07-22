#ifndef MPED_EVALUATIONFUNCTIONS_H
#define MPED_EVALUATIONFUNCTIONS_H

double compute_f(const std::vector<DelimitedSequence>& v, const std::vector<DelimitedSequence>& w,
                 const MatchingSchema &m, SparseDictionary& dict) {

    // compute Jaro for each pair
    std::vector<double> jaros;
    for (size_t i = 0; i < v.size(); i++)
        jaros.push_back(Jaro::compute(v[i], w[i], m, dict));

    double sum = std::accumulate(jaros.begin(), jaros.end(), 0.0);
    return sum / (double) jaros.size();
}

double compute_f(const std::vector<DelimitedSequence>& v, const std::vector<DelimitedSequence>& w, unsigned* sig1, unsigned* sig2,
                 const MatchingSchema &m, SparseDictionary& dict) {

    // compute Jaro for each pair
    std::vector<double> jaros;
    for (size_t i = 0; i < v.size(); i++)
        jaros.push_back(Jaro::compute(v[i], w[i], sig1, sig2, m, dict));

    double sum = std::accumulate(jaros.begin(), jaros.end(), 0.0);
    return sum / (double) jaros.size();
}

#endif //MPED_EVALUATEFUNCTIONS_H
