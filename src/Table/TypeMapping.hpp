#ifndef TYPE_MAPPING_CLASS
#define TYPE_MAPPING_CLASS

#include <string>
#include <map>
#include <vector>

#include "../DataType.hpp"

static std::map<std::string, DataType> raw_to_data_type = {
    {"string", DataType::STRING},
    {"number", DataType::NUMBER},
    {"date", DataType::DATE}};

static std::map<DataType, std::string> data_type_to_raw = {
    {DataType::STRING, "string"},
    {DataType::NUMBER, "number"},
    {DataType::DATE, "date"}};

class TypeMapping
{
public:
    static TypeMapping create(std::vector<std::string>);
    void insert(std::string, DataType);
    void insert(std::string key, std::string value);
    bool has(std::string key);
    DataType get(std::string &key);
    void print_mapping(void (*iteratee)(std::string key_value));

private:
    std::string valid_types = "string, number, date";
    std::map<std::string, DataType> current_type_mapping;
};

#endif
