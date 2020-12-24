#ifndef SAMPLER
#define SAMPLER

#include <vector>
#include <string>
#include <map>

#include "Collection.hpp"
#include "TypeMapping.hpp"

typedef std::vector<std::string> SampleData;

class Sampler : public Collection<std::string>
{
public:
    TypeMapping to_type_mapping();
    std::vector<SampleData> *get_sample_data();
};

#endif
