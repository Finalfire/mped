#ifndef MPED_NLPMATCHINGSCHEMA_H
#define MPED_NLPMATCHINGSCHEMA_H

#include "../Utility.h"
#include "../DelimitedSequence.h"
#include "../MatchingSchema.h"
#include "Dictionary.h"

class NLPMatchingSchema : public MatchingSchema {
public:
    Dictionary dict;

    DelimitedSequence a;
    DelimitedSequence b;

    NLPMatchingSchema(const size_t& a, const size_t& b, const size_t& c, const size_t& d,
                      const bool x, const Dictionary& dict1, const DelimitedSequence& s1,
                      const DelimitedSequence& s2) : MatchingSchema(a, b, c, d, x), dict(dict1), a(s1), b(s2) {
        // only for dic
        set_specific(!x);
    }

    /**
     * Check all the words in both sigma_1 and sigma_2.
     * For each pair -> check if the dict contains it and set the match in the ms.
     * @param value value to set for the match (true or false)
     */
    void set_specific(bool value) {
        for (unsigned i = 0; i < a.getSigma().size(); i++)
            for (unsigned j = 0; j < b.getSigma().size(); j++)
                if (i != j && dict.match(a.getSigma().at(i), b.getSigma().at(j)))
                    ms[i][j] = value;
    }

    /*const bool match(const unsigned& i, const unsigned& j) {
        return dict.match(dict.getA().getSequence()[i], dict.getB().getSequence()[i]);
    }*/
};


#endif //MPED_NLPMATCHINGSCHEMA_H
