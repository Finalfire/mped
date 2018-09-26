#ifndef MPED_MEGASIGMA_H
#define MPED_MEGASIGMA_H

#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <map>

class MegaSigma {
private:

    std::map<std::string, unsigned> mapping;

    std::vector<std::string> symbols;
    std::vector<unsigned> repr;

    size_t start_sigma;

    std::vector<std::string> symbols_dict;
    std::vector<std::string> symbols_sigma;

public:

    MegaSigma(const std::vector<std::string>& dict, const std::string& str) {
        unsigned value = 0;

        // first, copy all words from dict to symbols
        symbols_dict = dict;
        for (auto x: symbols_dict) {
            symbols.push_back(x);
            mapping.insert(std::pair<std::string, unsigned>(x, value++));
        }

        start_sigma = symbols.size();

        // first tokenize
        // then for each token:
        //      check if in symbols_dict: do nothing,
        //      else: append in symbols[_sigma]
        std::istringstream ss{str};
        using StrIt = std::istream_iterator<std::string>;
        std::vector<std::string> container{StrIt{ss}, StrIt{}};

        for (auto x: container) {
            //std::vector<std::string>::const_iterator it = std::find(symbols.begin(), symbols.end(), x);
            std::map<std::string, unsigned>::const_iterator it = mapping.find(x);
            //if (it == symbols.end()) {
            if (it == mapping.end()) {
                symbols_sigma.push_back(x);
                symbols.push_back(x);
                mapping.insert(std::pair<std::string, unsigned>(x, value++));
            }
         }

         // make the representation
        std::iota(repr.begin(), repr.end(), 0);
    }

    const std::map<std::string, unsigned int> &getMapping() const {
        return mapping;
    }

    const std::vector<std::string> &getSymbols() const {
        return symbols;
    }

    const std::vector<unsigned int> &getRepr() const {
        return repr;
    }

    const std::vector<std::string> &getSymbols_dict() const {
        return symbols_dict;
    }

    const std::vector<std::string> &getSymbols_sigma() const {
        return symbols_sigma;
    }

    size_t getStart_sigma() const {
        return start_sigma;
    }

};

#endif //MPED_MEGASIGMA_H
