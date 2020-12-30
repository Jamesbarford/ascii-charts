#ifndef PARSERS_H
#define PARSERS_H

#include <vector>
#include "../Table/Datum.hpp"
#include "../Table/TypeMapping.hpp"
#include "../DataType.hpp"

/*** Solidify this
 * Contains information about how likely a columns data type is
 * 
 * The DataType with the highest type count will be taken to be a columns type
 * 
 * patterns:
 * Stores the patterns encountered while deducing types.
 * Example:
 * date:
 * {"%Y-%m-%d", %m/%d/%Y} -> we now have the possible options and COULD present them back, currently we'll take the first one
 * float:
 * {
 *      "USD",
 *      "PERCENTAGE",
 *      "RAW_NUMBER" ->
 * } 
 * string:
 * {"STRING"} -> effectively sets up an identity function
 * 
 * This is a plausible outcome:
 * std::set<std::string> = {"STRING", "%Y-%m-%d", %m/%d/%Y}
 */
struct TypeHeuristic
{
	void increment(DataType type);
	std::map<DataType, int> type_count = {
		{DataType::_NUMBER, 0},
		{DataType::_STRING, 0},
		{DataType::_DATE, 0},
		{DataType::_FLOAT, 0}};
	std::vector<PatternHex> patterns;
};

DataType get_data_type(std::string raw_data);
std::vector<Datum> create_datum_vector(std::vector<std::string> *raw_data, std::map<int, std::string> *headers, TypeMapping *type_mapping);
TypeMapping create_type_mapping(std::vector<std::vector<std::string>> rows, std::vector<std::string> row_names);
TypeMapping _create_type_mapping(std::map<std::string, TypeHeuristic> type_heuristics);
std::map<std::string, TypeHeuristic> _create_type_heuristic(std::vector<std::vector<std::string>> rows, std::vector<std::string> row_names);
Datum create_datum(std::string *raw_data, DataType type, PatternHex pattern);
PatternHex get_pattern(std::string *raw_data, DataType type);
PatternHex get_valid_pattern(DataType *type, std::vector<PatternHex> *patterns);

#endif
