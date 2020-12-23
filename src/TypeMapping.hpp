#include <string>
#include <map>
#include <vector>

#include "TypeDefs.hpp"

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
