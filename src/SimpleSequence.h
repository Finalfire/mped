#ifndef MPED_SIMPLESEQUENCE_H
#define MPED_SIMPLESEQUENCE_H

#include <map>
#include <string>
#include <vector>
#include "AbstractSequence.h"
#include <iostream>

constexpr unsigned short _ASCII_LEN = 255 - 0;

class SimpleSequence : public AbstractSequence {
private:

    std::map<char, unsigned> mapping;

    std::string sigma;

    void extract_symbols() {
        // Bitset is being used because it allows us to
        // avoid the sort of the symbols for making the alphabet
        std::bitset<_ASCII_LEN> symbols;

        // Here the ASCII value is used to index the bitset
        for (char i : this->base)
            symbols[(int) i] = (symbols[(int) i] || true);

        // Lexicographic order
        for (size_t i = 0; i < _ASCII_LEN; ++i)
            if (symbols[i])
                this->sigma += (char) i;
    }

    void define_mapping() {
        for (size_t i = 0; i < this->sigma.size(); ++i)
            mapping.insert(std::pair<char, unsigned>(this->sigma[i], i));
    }

    void make_representations() {
        // Sigma representation is always 0..m-1
        for (unsigned i = 0; i < this->sigma.size(); )
            this->sigma_repr.push_back(i++);

        // Mapping from the alphabet
        for (unsigned i = 0; i < this->base.size(); )
            this->sequence_repr.push_back(this->mapping[this->base[i++]]);
    }

    void init() {
        extract_symbols();
        define_mapping();
        make_representations();
    }

public:
    SimpleSequence() = default;
    SimpleSequence(const std::string& s) : AbstractSequence(s) { init(); }
    SimpleSequence(const char* c) : AbstractSequence(c) { init(); }

    const std::string &getSequence() const {  return base; }
    const std::string &getSigma() const { return sigma; }
};

#endif //MPED_SIMPLESEQUENCE_H
