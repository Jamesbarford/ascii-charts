#include <variant>
#include <iostream>
#include <iomanip>
#include <vector>

#include "../Table/TypeMapping.hpp"
#include "../DataType.hpp"
#include "../util/string_util.hpp"
#include "numeric_parser.hpp"
#include "date_parser.hpp"
#include "parser.hpp"

void TypeHeuristic::increment(DataType type)
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
			std::string raw_data = row.at(column_idx);
			DataType type = get_data_type(raw_data);
			DataPattern pattern = get_pattern(&raw_data, type);

			TypeHeuristic *heuristic = &type_heuristics.at(row_name);
			if (std::find(heuristic->patterns.begin(), heuristic->patterns.end(), pattern) == heuristic->patterns.end())
				heuristic->patterns.push_back(pattern);

			heuristic->increment(type);
		}
	}

	return type_heuristics;
}

TypeMapping _create_type_mapping(std::map<std::string, TypeHeuristic> type_heuristics)
{
	TypeMapping type_mapping;
	DataType type = DataType::STRING;
	DataPattern pattern = "STRING";
	int count = 0;

	for (auto &heuristics : type_heuristics)
	{
		for (auto data_type : data_types)
		{
			int heuristic_count = heuristics.second.type_count.at(data_type);
			if (heuristic_count > count)
			{
				count = heuristic_count;
				type = data_type;
				pattern = heuristics.second.patterns.at(0);
			}
		}

		TypeMap type_map = {type, pattern};

		type_mapping.insert(heuristics.first, type_map);
		count = 0;
		type = DataType::STRING;
		pattern = "STRING";
	}

	return type_mapping;
}

std::string get_pattern(std::string *raw_data, DataType type)
{
	switch (type)
	{
	case DataType::NUMBER:
		return RAW_NUMBER;
	case DataType::STRING:
		return "STRING";
	case DataType::DATE:
		return get_date_pattern(raw_data);
		break;
	case DataType::FLOAT:
		return get_numeric_type(raw_data);

	default:
		return "STRING";
	}
}

DataType get_data_type(std::string raw_data)
{
	if (is_currency(raw_data) || is_float(raw_data) || is_percent(raw_data))
		return DataType::FLOAT;
	if (is_number(raw_data))
		return DataType::NUMBER;
	if (is_date(raw_data))
		return DataType::DATE;

	return DataType::STRING;
}

std::vector<Datum> create_datum_vector(std::vector<std::string> *raw_data, std::map<int, std::string> *headers, TypeMapping *type_mapping)
{
	std::vector<Datum> datums;
	for (size_t i = 0; i < raw_data->size(); ++i)
	{
		std::string header = headers->at(i);
		datums.push_back(create_datum(&raw_data->at(i), type_mapping->get(header).type, type_mapping->get(header).pattern));
	}
	return datums;
}

Datum create_datum(std::string *raw_data, DataType type, DataPattern pattern)
{
	Datum d;
	size_t s;

	switch (type)
	{
	case DataType::NUMBER:
		d.insert(Entry(std::stoll(*raw_data, &s)), DataType::NUMBER);
		break;

	case DataType::STRING:
		d.insert(Entry(*raw_data), DataType::STRING);
		break;

	case DataType::DATE:
	{
		long parsed_date = parse_date(raw_data, &pattern);
		d.insert(Entry(parsed_date), DataType::DATE);
		break;
	}

	case DataType::FLOAT:
	{
		long double parsed_number = parse_number(raw_data, &pattern);
		d.insert(Entry(parsed_number), DataType::FLOAT);
		break;
	}
	}

	return d;
}
