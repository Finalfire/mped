#ifndef MPED_SPARSEDICTIONARY_H
#define MPED_SPARSEDICTIONARY_H

#include <fstream>

class SparseDictionary {
private:
    typedef std::vector<bool> row;
    std::vector<row> dictionary;

    // input file of the dictionary
    std::string file;

    // collection of all words
    std::vector<std::string> collection;

    // unique lemmas
    std::vector<std::string> en_lemma;
    std::vector<std::string> it_lemma;

    std::map<std::string, unsigned> en_map;
    std::map<std::string, unsigned> it_map;

    void parse() {
        std::fstream f;
        f.open(file, std::fstream::in);

        // collect all words
        // this works due to the dictionary syntax being
        // word_en_1 word_it_1
        // ...
        // word_en_n word_it_n
        std::string temp;
        while (f.good()) {
            f >> temp;
            collection.push_back(temp);
        }

        f.close();
    }

    void build() {
        // populate unique lemma
        for (size_t i = 0; i < collection.size(); i += 2) {
            // en
            if (en_map.find(collection[i]) == en_map.end()) {
                en_lemma.push_back(collection[i]);
                en_map.insert(std::pair<std::string, unsigned>(collection[i], en_lemma.size()-1));
            }

            // it
            if (it_map.find(collection[i + 1]) == it_map.end()) {
                it_lemma.push_back(collection[i + 1]);
                it_map.insert(std::pair<std::string, unsigned>(collection[i + 1], it_lemma.size()-1));
            }
        }

        // define and init the matrix
        for (size_t i = 0; i < en_lemma.size(); i++)
            dictionary.push_back(row(it_lemma.size(), false));

        // for each pair in the dict <a,b> -> dictionary[index(a)][index(b)] = true
        for (size_t i = 0; i < collection.size(); i += 2)
            dictionary[en_map.at(collection[i])][it_map.at(collection[i+1])] = true;
    }

    void init() {
        parse();
        build();
    }

public:
    SparseDictionary(std::string& file) {
        this->file = file;
        init();
    }

    SparseDictionary(const char* file) {
        this->file = std::string(file);
        init();
    }

    const std::map<std::string, unsigned int> &getEn_map() const {
        return en_map;
    }

    const std::map<std::string, unsigned int> &getIt_map() const {
        return it_map;
    }

    const std::vector<std::string>& getEn_lemma() const {
        return en_lemma;
    }

    const std::vector<std::string>& getIt_lemma() const {
        return it_lemma;
    }

    /*
     * It checks where there exists a pair `<a,b>` in the dictionary
     * where `a` is a word in the english collection and `b` is a word in the italian one
     */
    const bool match(const std::string& a, const std::string& b) const {
        std::map<std::string, unsigned>::const_iterator en_word_index = en_map.find(a);
        std::map<std::string, unsigned>::const_iterator it_word_index = it_map.find(b);

        if (en_word_index != en_map.end() && it_word_index != it_map.end())
            return dictionary[en_word_index->second][it_word_index->second];

        return false;
    }
};

#endif //MPED_SPARSEDICTIONARY_H
