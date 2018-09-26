#ifndef MPED_EVALUATIONFUNCTIONS_H
#define MPED_EVALUATIONFUNCTIONS_H

class EvaluationFunctions {

public:

    /// Computes the Jaro distance for each pair {a,b} of strings using sigma permutations,
    /// then returns the weighted (on max length) avg over all pairs.
    /// @param v
    /// @param w
    /// @param sig1
    /// @param sig2
    /// @param m
    /// @param dict
    /// @return weighted avg over all pairs of strings
    static double compute_jaro_wavg_ws(const std::vector<DelimitedSequence> &v, const std::vector<DelimitedSequence> &w,
                                unsigned *sig1, unsigned *sig2,
                                const NLPMatchingSchemaFixed &m, SparseDictionary &dict) {

        // indexes used for the lookup on the matching schema
        std::vector<unsigned> sig1_index(v[0].sigma_len());
        for (unsigned i = 0; i < v[0].sigma_len(); i++)
            sig1_index[sig1[i]] = i;

        std::vector<unsigned> sig2_index(w[0].sigma_len());
        for (unsigned i = 0; i < w[0].sigma_len(); i++)
            sig2_index[sig2[i]] = i;

        // compute Jaro for each pair
        //std::vector<double> distances;
        double distance = 0.0;
        double weights = 0.0;
        size_t max_length = 0;

        for (size_t i = 0; i < v.size(); i++) {
            for (size_t j = i; j < w.size(); j++) {
                max_length = std::max(v[i].seq_len(), w[j].seq_len());
                //distances.push_back(Jaro::compute_ws(v[i], w[j], sig1, sig2, m, dict, sig1_index, sig2_index) * (double) max_length);
                distance += (Jaro::compute_ws(v[i], w[j], sig1, sig2, m, dict, sig1_index, sig2_index) *
                             (double) max_length);
                weights += (double) max_length;
            }
        }

        //double sum = std::accumulate(distances.begin(), distances.end(), 0.0);
        return distance / weights;
    }

    /**
     * Computes the Jaro distance for each pair {a,b} of strings using only the dict (case pi = 0)
     * then returns the weighted (on max length) avg over all pairs.
     * @param v
     * @param w
     * @param sig1
     * @param sig2
     * @param m
     * @param dict
     * @return weighted avg over all pairs of strings
     */
    static double compute_jaro_wavg_only_dict_ws(const std::vector<DelimitedSequence> &v, const std::vector<DelimitedSequence> &w,
                                   SparseDictionary &dict) {

        // compute Jaro for each pair
        //std::vector<double> distances;
        double distance = 0.0;
        double weights = 0.0;
        size_t max_length = 0;

        for (size_t i = 0; i < v.size(); i++) {
            for (size_t j = i; j < w.size(); j++) {
                max_length = std::max(v[i].seq_len(), w[j].seq_len());
                //distances.push_back(Jaro::compute_only_dict(v[i], w[j], dict) * (double) max_length);
                distance += (Jaro::compute_only_dict(v[i], w[j], dict) * (double) max_length);
                weights += (double) max_length;
            }
        }

        //double sum = std::accumulate(distances.begin(), distances.end(), 0.0);
        return distance / weights;
    }

};

#endif //MPED_EVALUATEFUNCTIONS_H
