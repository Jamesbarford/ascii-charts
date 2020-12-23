#include <string>
#include <map>

#include "TypeDefs.hpp"
#include "TypeMapping.hpp"

static std::map<std::string, DATA_TYPE> raw_to_data_type = {
    {"string", DATA_TYPE::STRING},
    {"number", DATA_TYPE::NUMBER},
    {"date", DATA_TYPE::DATE}};

static std::map<DATA_TYPE, std::string> data_type_to_raw = {
    {DATA_TYPE::STRING, "string"},
    {DATA_TYPE::NUMBER, "number"},
    {DATA_TYPE::DATE, "date"}};

void TypeMapping::insert(std::string key, DATA_TYPE type)
{
    current_type_mapping.insert({key, type});
}

void TypeMapping::insert(std::string key, std::string value)
{
    if (raw_to_data_type.count(value) == 0)
        throw std::invalid_argument("Invalid type valid type : '" + value + "' valid types: " + valid_types);

    current_type_mapping.insert({key, raw_to_data_type.at(value)});
}

bool TypeMapping::has(std::string key)
{
    if (current_type_mapping.find(key) != current_type_mapping.end())
        return true;
    return false;
}

DATA_TYPE TypeMapping::get(std::string &key)
{
    if (!has(key))
        throw std::invalid_argument("No mapping for key : " + key);
    return current_type_mapping.at(key);
}

void TypeMapping::print_mapping(void (*iteratee)(std::string key_value))
{
    for (auto &entry : current_type_mapping)
        iteratee(entry.first + ":" + data_type_to_raw.at(entry.second));
}