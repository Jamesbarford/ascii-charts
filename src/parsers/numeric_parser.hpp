#ifndef NUMERIC_PARSER_H
#define NUMERIC_PARSER_H

#include "../DataType.hpp"

bool is_integer(const std::string &s);
bool is_float(const std::string &s);
bool is_currency(const std::string &s);
bool is_currency(const std::string &s);
bool is_percent(const std::string &s);
long double parse_number(std::string *str, Hex pattern);
std::string remove_currency(std::string *str_num);
std::string remove_percentage(std::string *str_num);
std::string remove_non_numeric(std::string *str);
Hex get_numeric_type(std::string *str);
Hex _get_numeric_type(std::string *str, char const **tokens);
#endif
