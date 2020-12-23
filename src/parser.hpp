#include <string>
#include <map>

#include "TypeDefs.hpp"
#include "Datum.hpp"
#include "TypeMapping.hpp"

struct TypeHeuristic
{
    std::map<DATA_TYPE, int> type_count = {
        {DATA_TYPE::NUMBER, 0},
        {DATA_TYPE::STRING, 0},
        {DATA_TYPE::DATE, 0}};
    void increment(DATA_TYPE type);
};

bool is_number(const std::string &s);
DATA_TYPE get_data_type(std::string raw_data);
Datum create_datum(std::string raw_data, DATA_TYPE type);
TypeMapping create_type_mapping(std::vector<std::vector<std::string>> rows, std::vector<std::string> row_names);
TypeMapping _create_type_mapping(std::map<std::string, TypeHeuristic> type_heuristics);
std::map<std::string, TypeHeuristic> _create_type_heuristic(std::vector<std::vector<std::string>> rows, std::vector<std::string> row_names);
