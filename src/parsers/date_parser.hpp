#ifndef DATE_PARSER_H
#define DATE_PARSER_H

#include <vector>
#include <string>
#include "../DataType.hpp"

bool is_date(std::string date_string);
long parse_date(std::string *date_string);
long parse_date(std::string *date_string, Hex pattern);
long parse_date(std::string *date_string, std::string *pattern);
std::string get_milliseconds(std::string date_string, Hex pattern);
Hex get_date_pattern(std::string *date_string);
Hex get_date_pattern(std::string *date_string, const int *patters);

#endif
