#include <variant>
#include <iostream>
#include <iomanip>
#include <vector>

#include "parser.hpp"
#include "TypeMapping.hpp"

void TypeHeuristic::increment(DATA_TYPE type)
{
    type_count.at(type)++;
}

TypeMapping create_type_mapping(std::vector<std::vector<std::string>> rows, std::vector<std::string> row_names)
{
    std::map<std::string, TypeHeuristic> type_heuristics = _create_type_heuristic(rows, row_names);
    return _create_type_mapping(type_heuristics);
}

std::map<std::string, TypeHeuristic> _create_type_heuristic(std::vector<std::vector<std::string>> rows, std::vector<std::string> row_names)
{
    int row_idx, column_idx;
    std::map<std::string, TypeHeuristic> type_heuristics;

    for (auto &row_name : row_names)
    {
        TypeHeuristic t;
        type_heuristics.insert({row_name, t});
    }

    for (int row_idx = 0; row_idx < rows.size(); ++row_idx)
    {
        std::vector<std::string> row = rows.at(row_idx);
        for (int column_idx = 0; column_idx < row.size(); ++column_idx)
        {
            std::string row_name = row_names.at(column_idx);
            DATA_TYPE type = get_data_type(row.at(column_idx));

            type_heuristics.at(row_name).increment(type);
        }
    }

    return type_heuristics;
}

TypeMapping _create_type_mapping(std::map<std::string, TypeHeuristic> type_heuristics)
{
    TypeMapping type_mapping;
    DATA_TYPE type = DATA_TYPE::STRING;
    int count = 0;

    for (auto heuristics : type_heuristics)
    {
        for (auto data_type : data_types)
        {
            int heuristic_count = heuristics.second.type_count.at(data_type);
            if (heuristic_count > count)
            {
                count = heuristic_count;
                type = data_type;
            }
        }
        type_mapping.insert(heuristics.first, type);
        count = 0;
        type = DATA_TYPE::STRING;
    }

    return type_mapping;
}

DATA_TYPE get_data_type(std::string raw_data)
{
    if (is_number(raw_data))
        return DATA_TYPE::NUMBER;

    return DATA_TYPE::STRING;
}

std::vector<Datum> create_datum_vector(std::vector<std::string> *raw_data, std::map<int, std::string> *headers, TypeMapping *type_mapping)
{
    std::vector<Datum> datums;
    for (size_t i = 0; i < raw_data->size(); ++i)
    {
        std::string header = headers->at(i);
        datums.push_back(create_datum(raw_data->at(i), type_mapping->get(header)));
    }
    return datums;
}

Datum create_datum(std::string raw_data, DATA_TYPE type)
{
    Datum d;

    switch (type)
    {
    case DATA_TYPE::NUMBER:
        size_t s;
        d.insert(Entry(std::stold(raw_data, &s)), DATA_TYPE::NUMBER);
        break;

    case DATA_TYPE::DATE:
        d.insert(Entry(std::stol(raw_data)), DATA_TYPE::DATE);
        break;

    default:
        d.insert(Entry(raw_data), DATA_TYPE::STRING);
    }

    return d;
}

bool is_number(const std::string &s)
{
    auto predicate = [](unsigned char c) -> bool {
        return !std::isdigit(c);
    };

    return !s.empty() && std::find_if(s.begin(), s.end(), predicate) == s.end();
}