#ifndef MPED_DELIMITEDSEQUENCE_H_
#define MPED_DELIMITEDSEQUENCE_H_

#include <map>
#include <sstream>
#include <string>
#include <vector>


class DelimitedSequence {
private:
    std::string seq;
    std::string delimiter;

    std::map<std::string, unsigned> mapping;

    std::vector<std::string> tokseq;
    std::vector<std::string> tokens;

    std::vector<unsigned> seq_repr;
    std::vector<unsigned> tokens_repr;

    void extract_tokens() {
        // (1) tokenize seq for whitespace
        std::istringstream ss{this->seq};
        using StrIt = std::istream_iterator<std::string>;
        std::vector<std::string> container{StrIt{ss}, StrIt{}};

        // (1.1) save the tokenized sequence
        tokseq = container;

        // (2) save distinct tokens
        std::sort(container.begin(), container.end());
        auto it = std::unique(container.begin(), container.end());
        for (auto i = container.begin(); i != it; i++)
            tokens.push_back(*i);
    }

    void define_mapping() {
        unsigned i = 0;
        for (auto x: tokens)
            mapping.insert(std::pair<std::string, unsigned>(x, i++));
    }

    void fill_representation() {
        // unsigned representation of the sequence
        for (auto x: tokseq)
            seq_repr.push_back(mapping.at(x));

        // unsigned representation of the token alphabet
        for (auto x: tokens)
            tokens_repr.push_back(mapping.at(x));
    }

    void init() {
        extract_tokens();
        define_mapping();
        fill_representation();
    }

public:

    DelimitedSequence() = default;

    explicit DelimitedSequence(const char* s, const char* d) : seq(s), delimiter(d) {
        init();
    }

    explicit DelimitedSequence(std::string&& s, std::string&& d)  {
        seq = std::move(s);
        delimiter = std::move(d);

        init();
    }

    const std::vector<std::string>& getTokens() const { return tokens; }
    const std::map<std::string, unsigned int>& getMapping() const { return mapping; }
    const std::vector<unsigned int> &getSeq_repr() const { return seq_repr; }
    const std::vector<unsigned int> &getTokens_repr() const { return tokens_repr; }
    const std::vector<unsigned int> &getSigma_repr() const { return tokens_repr; }

    const size_t seq_len() const { return seq_repr.size(); }
    const size_t sigma_len() const { return tokens_repr.size(); }

};


#endif //MPED_DELIMITEDSEQUENCE_HPP
