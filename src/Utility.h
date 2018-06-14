#ifndef UTILITY_H_
#define UTILITY_H_

#include <climits>
#include <sstream>
#include <vector>
#include "MatchingSchema.h"

// a pair representing a constraint pair
typedef std::pair<char, char> p_constr;

typedef std::pair<int, int> cell;

/* Utility functions */
unsigned fast_atoi(const char* str) {
    unsigned val = 0;
    while (*str) val = val*10 + (*str++ - '0');
    return val;
}

inline const int min(const int a, const int b, const int c) {
    if ((a<=b) && (a<=c)) return a;
    else if ((b<=a) && (b<=c)) return b;
    else return c;
}

inline void read_stdin(std::string& a, std::string& b) {
    getline(std::cin, a);
    getline(std::cin, b);
}

template <typename T>
inline void print(T x) { std::cout << x << std::endl; }

inline void printX(int x) {
    std::cout << x << std::endl;
}


/* USED FOR HILL CLIMBING HEURISTIC */

int index_of(const unsigned& x, unsigned*& s, const size_t& n) {
    for (size_t i = 0; i < n; ++i)
        if (s[i] == x)
            return (int) i;
    return -1;
}

int index_of(const unsigned short& x, const std::vector<unsigned short>& s, const size_t& n) {
    for (size_t i = 0; i < n; ++i)
        if (s.at(i) == x)
            return i;
    return -1;
}

int number_of_single_repetition(const unsigned& x, const unsigned* s, const size_t& n) {
    int k=0;
    for (size_t i = 0; i < n; ++i)
        if (s[i] == x)
            k++;
    return k;
}

// Fisher-Yates shuffle
void shuffle(std::vector<unsigned>& a, size_t s) {
    size_t j = 0;
    unsigned short t = 0;
    for (size_t i = s-1; i > 0; i--) {
        j = rand() % (i+1);
        t = a[j]; a[j] = a[i]; a[i] = t;
    }
}

void shuffle(unsigned*& a, size_t s) {
    size_t j = 0;
    unsigned short t = 0;
    for (size_t i = s-1; i > 0; i--) {
        j = rand() % (i+1);
        t = a[j]; a[j] = a[i]; a[i] = t;
    }
}

bool isValid(std::vector<unsigned>& s, int s_size, int p) {
    int currentMin = INT_MAX-1;
    int lastMin = INT_MAX;

    for (int i = 0; i < s_size; i++) {
        if (currentMin > s[i])
            currentMin = s[i];

        if (i >= p)
            if (lastMin > currentMin)
                return false;

        if ((i % p) == (p-1)) {
            lastMin = currentMin;
            currentMin = INT_MAX;
        }
    }
    return true;
}

bool isValid(unsigned*& s, int s_size, int p) {
    int currentMin = INT_MAX-1;
    int lastMin = INT_MAX;

    for (int i = 0; i < s_size; i++) {
        if (currentMin > s[i])
            currentMin = s[i];

        if (i >= p)
            if (lastMin > currentMin)
                return false;

        if ((i % p) == (p-1)) {
            lastMin = currentMin;
            currentMin = INT_MAX;
        }
    }
    return true;
}

#endif /* UTILITY_H_ */
