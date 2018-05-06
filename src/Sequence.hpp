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
        std::bitset<_ASCII_LEN> symbols;

        for (size_t i = 0; i < this->seq.size(); i++)
            symbols[(int) this->seq[i]] = (symbols[(int) this->seq[i]] || 1);

        for (size_t i = 0; i < _ASCII_LEN; ++i)
            if (symbols[i])
                this->sigma += (char) i;
    }

    void define_mapping() {
        for (size_t i = 0; i < this->sigma.size(); ++i)
            mapping.insert(std::pair<char, unsigned>(this->sigma[i], i));
    }

    void make_representations() {
        for (unsigned i = 0; i < this->sigma.size(); )
            this->sigma_repr.push_back(i++);
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

    explicit Sequence(const std::string& s) : seq(s) {
        init();
    }

    const std::string &getSeq() const {
        return seq;
    }

    const std::string &getSigma() const {
        return sigma;
    }

    const std::vector<unsigned int> &getSeq_repr() const {
        return seq_repr;
    }

    const std::vector<unsigned int> &getSigma_repr() const {
        return sigma_repr;
    }
};

#endif