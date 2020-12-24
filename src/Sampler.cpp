#include <map>
#include <string>
#include <iostream>

#include "Sampler.hpp"
#include "parser.hpp"
#include "TypeDefs.hpp"
#include "Table.hpp"

TypeMapping Sampler::to_type_mapping()
{
    std::vector<std::string> header_vec;
    for (auto header : this->headers)
        header_vec.push_back(header.second);

    return create_type_mapping(this->data, header_vec);
}

std::vector<std::vector<std::string>> *Sampler::get_sample_data()
{
    return &data;
}