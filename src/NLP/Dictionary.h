#ifndef MPED_VOCABULARY_H
#define MPED_VOCABULARY_H

#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "../AbstractSequence.h"


class Dictionary {
private:

    // word -> integer (for the fast lookup in the vectors)
    std::map<std::string, unsigned> en_map;
    std::map<std::string, unsigned> it_map;

    // input file of the dictionary
    std::string file;

    // words used in the lemma
    std::vector<std::string> en_lemma;
    std::vector<std::string> it_lemma;

    // init the dictionary
    void init_1to1() {
        std::fstream f;
        f.open(file, std::fstream::in);

        unsigned i = 0;
        std::string temp;
        while (f.good()) {
            f >> temp;
            en_lemma.push_back(temp);
            en_map.insert(std::pair<std::string, unsigned>(temp, i));

            f >> temp;
            it_lemma.push_back(temp);
            it_map.insert(std::pair<std::string, unsigned>(temp, i));

            i++;
        }
        f.close();
    }

public:

    Dictionary(std::string& file) {
        this->file = file;
        init_1to1();
    }

    Dictionary(const char* file) {
        this->file = std::string(file);
        init_1to1();
    }

    const std::vector<std::string>& getEn_lemma() const {
        return en_lemma;
    }

    const std::vector<std::string>& getIt_lemma() const {
        return it_lemma;
    }

    // a is in eng, b is in ita
    const bool match(const std::string& a, const std::string& b) {
        std::map<std::string, unsigned>::iterator en_word_index = en_map.find(a);
        std::map<std::string, unsigned>::iterator it_word_index = it_map.find(a);

        if (en_word_index != en_map.end() && it_word_index != it_map.end())
            return en_lemma.at(en_word_index->second) == it_lemma.at(it_word_index->second);
        return false;
    }
};


#endif //MPED_VOCABULARY_H
