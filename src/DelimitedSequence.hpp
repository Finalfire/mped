#ifndef MPED_DELIMITEDSEQUENCE_HPP
#define MPED_DELIMITEDSEQUENCE_HPP

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

    const std::vector<std::string>& getTokens() const {
        return tokens;
    }

    const std::map<std::string, unsigned int>& getMapping() const { return mapping; }

};


#endif //MPED_DELIMITEDSEQUENCE_HPP
