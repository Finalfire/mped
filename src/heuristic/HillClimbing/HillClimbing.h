#ifndef MPED_HILLCLIMBING_H
#define MPED_HILLCLIMBING_H

#include "../Heuristic.h"
#include "../../sequence/AbstractSequence.h"

class HillClimbing : public Heuristic {

    unsigned compute_heuristic(const AbstractSequence&, const AbstractSequence&) {
        unsigned

        /*
         p = permutazione_di_partenza

         m = p.get_ms()
         d = distanza_attuale

         min_dist = d
         best_ms = 0

         top_dist = min_dist
         top_ms = 0

         improved = true
         while (improved):
            improved = false

            for (n: m.get_neighbours()):
                d = distanza_with_n

                if (d < min_dist):
                    min_dist = d
                    improved = true

                    best_ms = n

            if (improved):
                m = current_best_ms
                depth++
            else:
                if (min_dist < top_dist):
                    top_dist = min_dist
                    top_ms = best_ms

                    improved = true
                    attempts = 0
                    depth = 0

                if (attempts < max_attempts):
                    improved = true
                    attempts++

                    m = random_ms(m)
                    min_dist = distanza_with_m
                else:
                    # this is the end
                    final_ms = top_ms
                    final_dist = top_dist

         */

        return 0;
    };
};


#endif //MPED_HILLCLIMBING_H
