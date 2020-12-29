#include <map>
#include <string>
#include <iostream>

#include "../DataType.hpp"
#include "../parsers/parser.hpp"
#include "Sampler.hpp"
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

bool Sampler::should_collect(int row_idx, int column_idx)
{
    return !this->complete && (row_idx == this->sample_size) && (this->width() == column_idx);
}