#ifndef DATE_PARSER_H
#define DATE_PARSER_H

#include <vector>
#include <string>
#include "../DataType.hpp"

bool is_date(std::string date_string);
long parse_date(std::string *date_string);
long parse_date(std::string *date_string, PatternHex pattern);
long parse_date(std::string *date_string, std::string *pattern);
std::string get_milliseconds(std::string date_string, PatternHex pattern);
PatternHex get_date_pattern(std::string *date_string);
PatternHex get_date_pattern(std::string *date_string, std::vector<PatternHex> patterns);

#endif
