#include <map>
#include <string>
#include <iostream>

#include "Sampler.hpp"
#include "parser.hpp"
#include "TypeDefs.hpp"

// acting on one individual piece of data, i.e 1
void Sampler::collect(std::string raw_sample, int column_idx)
{
    if (column_idx + 1 == this->column_width)
    {
        this->current_sample.push_back(raw_sample);
        this->sample.push_back(this->current_sample);
        this->current_sample.clear();
    }
    else
        this->current_sample.push_back(raw_sample);
}

void Sampler::collect_headers(std::string header, int column_idx)
{
    this->headers.insert({column_idx, header});
    this->column_width++;
}

int Sampler::get_size()
{
    return this->sample.size();
}

std::vector<SampleData> *Sampler::get_parsed_data()
{
    return &sample;
}

TypeMapping Sampler::to_type_mapping()
{
    std::vector<std::string> header_vec;
    for (auto header : this->headers)
        header_vec.push_back(header.second);

    return create_type_mapping(this->sample, header_vec);
}

void Sampler::print()
{
    for (auto s : this->sample)
    {
        for (auto raw_data : s)
        {
            std::cout << raw_data << ",";
        }
        std::cout << "\n";
    }
}
void Sampler::print_headers()
{
    for (auto h : this->headers)
    {
        std::cout << h.second << ",";
    }
    std::cout << "\n";
}