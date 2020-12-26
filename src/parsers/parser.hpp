#ifndef PARSERS_H
#define PARSERS_H

#include <string>
#include <map>

#include "../DataType.hpp"
#include "../Table/Datum.hpp"
#include "../Table/TypeMapping.hpp"

struct TypeHeuristic
{
    void increment(DataType type);
    std::map<DataType, int> type_count = {
        {DataType::NUMBER, 0},
        {DataType::STRING, 0},
        {DataType::DATE, 0},
        {DataType::FLOAT, 0}};
};

DataType get_data_type(std::string raw_data);
Datum create_datum(std::string raw_data, DataType type);
std::vector<Datum> create_datum_vector(std::vector<std::string> *raw_data, std::map<int, std::string> *headers, TypeMapping *type_mapping);
TypeMapping create_type_mapping(std::vector<std::vector<std::string>> rows, std::vector<std::string> row_names);
TypeMapping _create_type_mapping(std::map<std::string, TypeHeuristic> type_heuristics);
std::map<std::string, TypeHeuristic> _create_type_heuristic(std::vector<std::vector<std::string>> rows, std::vector<std::string> row_names);

#endif
