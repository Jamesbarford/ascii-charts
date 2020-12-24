#ifndef SAMPLER
#define SAMPLER

#include <vector>
#include <string>
#include <map>

#include "Collection.hpp"
#include "TypeMapping.hpp"

class Sampler : public Collection<std::vector<std::string>, std::string>
{
public:
    TypeMapping to_type_mapping();
    bool complete = false;
    virtual std::string converter(std::string raw, int column_idx)
    {
        return raw;
    }
    std::vector<std::vector<std::string>> *get_sample_data();
};

#endif
