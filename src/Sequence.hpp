#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <bitset>
#include <map>
#include <numeric>
#include <string>
#include <vector>

constexpr unsigned short _ASCII_LEN = 255 - 0;

class Sequence {
private:
    std::string seq;
    std::string sigma;

    std::vector<unsigned> seq_repr;
    std::vector<unsigned> sigma_repr;

    std::map<char, unsigned> mapping;

    void extract_sigma() {
        // Bitset is being used because it allows us to
        // avoid the sort of the symbols for making the alphabet
        std::bitset<_ASCII_LEN> symbols;

        // Here the ASCII value is used to index the bitset
        for (char i : this->seq)
            symbols[(int) i] = (symbols[(int) i] || 1);

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
        for (unsigned i = 0; i < this->seq.size(); )
            this->seq_repr.push_back(this->mapping[this->seq[i++]]);
    }

    void init() {
        extract_sigma();
        define_mapping();
        make_representations();
    }

public:
    Sequence() = default;

    explicit Sequence(const char* s) : seq(s) {
        init();
    }

    explicit Sequence(std::string&& s)  {
        seq = std::move(s);
        init();
    }

    const std::string& getSeq() const {
        return seq;
    }

    const std::string& getSigma() const {
        return sigma;
    }

    const std::vector<unsigned int>& getSeq_repr() const {
        return seq_repr;
    }

    const std::vector<unsigned int>& getSigma_repr() const {
        return sigma_repr;
    }

    const size_t seq_len() const { return seq.size(); }
    const size_t sigma_len() const { return sigma.size(); }
};

#endif