#ifndef MPED_ABSTRACTSEQUENCE_H
#define MPED_ABSTRACTSEQUENCE_H

#include <string>
#include <vector>

class AbstractSequence {
protected:
    std::string base;

    std::vector<unsigned> sequence_repr;
    std::vector<unsigned> sigma_repr;

public:
    explicit AbstractSequence(const std::string& s) : base(s) {}
    explicit AbstractSequence(const char* s) : base(s) {}

    const size_t seq_len() const { return sequence_repr.size(); }
    const size_t sigma_len() const { return sigma_repr.size(); }

    const std::string& getBase() const { return base; }
    const std::vector<unsigned int> &getSequence_repr() const { return sequence_repr; }
    const std::vector<unsigned int> &getSigma_repr() const { return sigma_repr; }
};

#endif //MPED_ABSTRACTSEQUENCE_H
