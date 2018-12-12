#ifndef MPED_JARO_H
#define MPED_JARO_H

#include <iostream>
#include <vector>

#include "../sequence/DelimitedSequence.h"
#include "../MatchingSchema.h"
#include "../Utility.h"
#include "Metric.h"

class Jaro : public Metric {

public:

    Jaro(MatchingSchema* m) : Metric(m) {}

    double compute_distance_enhanced(const DelimitedSequence& a, const DelimitedSequence& b,
            const std::vector<unsigned>& sig1, const std::vector<unsigned>& sig2) {

        std::vector<unsigned> sig1_index(a.sigma_len());
        for (unsigned i = 0; i < a.sigma_len(); i++)
            sig1_index[sig1[i]] = i;

        std::vector<unsigned> sig2_index(b.sigma_len());
        for (unsigned i = 0; i < b.sigma_len(); i++)
            sig2_index[sig2[i]] = i;

        const uint l1 = a.seq_len();
        const uint l2 = b.seq_len();

        if (l1 == 0)
            return l2 == 0 ? 1.0 : 0.0;

        const uint match_distance = std::max(l1, l2) / 2 - 1;
        bool s1_matches[l1];
        bool s2_matches[l2];
        std::fill(s1_matches, s1_matches + l1, false);
        std::fill(s2_matches, s2_matches + l2, false);
        uint matches = 0;

        for (uint i = 0; i < l1; i++) {
            const int endd = std::min(i + match_distance + 1, l2);
            for (int k = max(0, i - match_distance); k < endd; k++) {
                if (!s2_matches[k] &&
                    ((!this->matchingSchema->ms[sig1_index[a.getSequence_repr()[i]]][sig2_index[b.getSequence_repr()[k]]]))) {

                    s1_matches[i] = true;
                    s2_matches[k] = true;
                    matches++;
                    break;
                }
            }
        }

        if (matches == 0)
            return 0.0;

        double t = 0.0;
        uint k = 0;
        for (uint i = 0; i < l1; i++)
            if (s1_matches[i]) {
                while (!s2_matches[k]) k++;
                if (!this->matchingSchema->ms[sig1_index[a.getSequence_repr()[i]]][sig2_index[b.getSequence_repr()[k]]]) t += 0.5;
                k++;
            }

        const double m = matches;
        return (m / l1 + m / l2 + (m - t) / m) / 3.0;
    }

    static double jaro(const std::string& s1, const std::string& s2) {
        const uint l1 = s1.length(), l2 = s2.length();
        if (l1 == 0)
            return l2 == 0 ? 1.0 : 0.0;
        const uint match_distance = std::max(l1, l2) / 2 - 1;
        bool s1_matches[l1];
        bool s2_matches[l2];
        std::fill(s1_matches, s1_matches + l1, false);
        std::fill(s2_matches, s2_matches + l2, false);
        uint matches = 0;
        for (uint i = 0; i < l1; i++)
        {
            const int end = std::min(i + match_distance + 1, l2);
            for (int k = std::max(0u, i - match_distance); k < end; k++)
                if (!s2_matches[k] && s1[i] == s2[k])
                {
                    s1_matches[i] = true;
                    s2_matches[k] = true;
                    matches++;
                    break;
                }
        }
        if (matches == 0)
            return 0.0;
        double t = 0.0;
        uint k = 0;
        for (uint i = 0; i < l1; i++)
            if (s1_matches[i])
            {
                while (!s2_matches[k]) k++;
                if (s1[i] != s2[k]) t += 0.5;
                k++;
            }

        const double m = matches;
        return (m / l1 + m / l2 + (m - t) / m) / 3.0;
    }
};


#endif //MPED_JACCARD_H
