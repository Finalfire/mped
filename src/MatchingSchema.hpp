#ifndef MATCHINGSCHEMA_H_
#define MATCHINGSCHEMA_H_

#include "Utility.h"

struct MatchingSchema {
    size_t n, m;
    size_t p1, p2;
    bool** ms;
    bool** chi;

    // x is the default boolean value for the matrix
    MatchingSchema(const size_t& a, const size_t& b, const size_t& c, const size_t& d, const bool x, bool def) : n(a), m(b), p1(c), p2(d) {
        ms = new bool*[n];
        for (size_t i = 0; i < n; ++i) ms[i] = new bool[m];

        chi = new bool*[n];
        for (size_t i = 0; i < n; ++i) chi[i] = new bool[m];

        init(x, def);
    }

    ~MatchingSchema() {
        for (size_t i = 0; i < n; ++i)
            delete[] ms[i];
        delete[] ms;

        for (size_t i = 0; i < n; ++i)
            delete[] chi[i];
        delete[] chi;
    }

    void init(bool b, bool d) {
        // setup the matching schema
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < m; ++j)
                ms[i][j] = b;
        // setup the constraints
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < m; ++j)
                chi[i][j] = d;
    }

    // e.g., if value == false, ms[i][j] == false means that i and j are in match
    void set_identity(std::string& sigma1, std::string& sigma2, bool value) {
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < m; ++j)
                if (sigma1[i] == sigma2[j])
                    ms[i][j] = value;
    }

    // e.g., if value == false, ms[i][j] == false means that i and j are in match
    void set_general(bool value) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (p1 !=0 && p2 !=0 && (i/p2 == j/p1))
                    ms[i][j] = value;
                else
                    ms[i][j] = !value;
    }

    void set_general_fibre(const std::vector<std::string>& sigma1, const std::vector<std::string>& sigma2, bool value) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (p1 !=0 && p2 !=0 && (i/p2 == j/p1))
                    ms[i][j] = value;
                else
                    ms[i][j] = !value;
    }

    void set_constraint(size_t i, size_t j, bool t) { chi[i][j] = t; }

    void print_matching_schema(const std::string& sigma1, const std::string& sigma2) {
        std::cout << "\t";
        for (int j = 0; j < m; ++j)
            std::cout << sigma2[j] << "\t";
        std::cout << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << sigma1[i] << "\t";
            for (int j = 0; j < m; ++j)
                std::cout << ms[i][j] << "\t";
            std::cout << std::endl;
        }
    }

    void shift(int startRow, int startCol, bool value){
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < m; ++j)
                ms[i][j] = true;

        for (int i = (startRow); i < n; ++i)
            for (int j = (startCol); j < m; ++j)
                if (p1 !=0 && p2 !=0 && ((i-(startRow))/p2 == (j-(startCol))/p1))
                    ms[i][j] = value;
    }
};

#endif
