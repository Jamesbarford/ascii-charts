#ifndef TYPE_MAPPING
#define TYPE_MAPPING

#include <string>
#include <map>
#include <vector>

#include "TypeDefs.hpp"

#pragma once
static std::map<std::string, DATA_TYPE> raw_to_data_type = {
    {"string", DATA_TYPE::STRING},
    {"number", DATA_TYPE::NUMBER},
    {"date", DATA_TYPE::DATE}};

#pragma once
static std::map<DATA_TYPE, std::string> data_type_to_raw = {
    {DATA_TYPE::STRING, "string"},
    {DATA_TYPE::NUMBER, "number"},
    {DATA_TYPE::DATE, "date"}};

#pragma once
class TypeMapping
{
public:
    static TypeMapping create(std::vector<std::string>);
    void insert(std::string, DATA_TYPE);
    void insert(std::string key, std::string value);
    bool has(std::string key);
    DATA_TYPE get(std::string &key);
    void print_mapping(void (*iteratee)(std::string key_value));

private:
    std::string valid_types = "string, number, date";
    std::map<std::string, DATA_TYPE> current_type_mapping;
};

#endif
