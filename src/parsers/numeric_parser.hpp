#ifndef NUMERIC_PARSER_H
#define NUMERIC_PARSER_H

#include "../DataType.hpp"

bool is_integer(const std::string &s);
bool is_float(const std::string &s);
bool is_currency(const std::string &s);
bool is_currency(const std::string &s);
bool is_percent(const std::string &s);
long double parse_number(std::string *str, PatternHex pattern);
std::string remove_currency(std::string *str_num);
std::string remove_percentage(std::string *str_num);
std::string remove_non_numeric(std::string *str);
PatternHex get_numeric_type(std::string *str);
PatternHex _get_numeric_type(std::string *str, std::vector<std::string>);
#endif
