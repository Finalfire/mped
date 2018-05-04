#include <string>
#include <vector>
#include <map>

class Sequence {
private:
    std::string sequence;
    std::vector<unsigned> representation;
    std::map<char, unsigned> mapping;

public:
    Sequence() {};

    Sequence(const std::string& s) : sequence(s) {
        unsigned index = 0;
        for (auto c : s)
            this->mapping.insert(std::pair<char, unsigned>(c, index++));
    };

    const std::string &getSequence() const {
        return sequence;
    }

    const std::vector<unsigned int> &getRepresentation() const {
        return representation;
    }

    const std::map<char, unsigned int> &getMapping() const {
        return mapping;
    }
};