#ifndef NUMERIC_PARSER_H
#define NUMERIC_PARSER_H

#define EURO "€"
#define USD "$"
#define STERLING "£"

#define DECIMAL_DELIMITER '.'
#define COMMA_DELIMITER ","
#define PERCENT_SYMBOL "%"

#define NULL_CURRENCY "not a currency"
#define NULL_PERCENT "not a percent"
#define INVALID_NUMERIC_FORMAT "invalid numeric format"
#define RAW_NUMBER "raw number"
#define INCLUDE_DECIMAL 1
#define ASCII_NUMERIC_START 48
#define ASCII_NUMERIC_END 57
#define ASCII_DECIMAL 46
#define ASCII_PERCENT 37
#define ASCII_COMMA 44

#include <map>
#include "../util/string_util.hpp"
#include "../DataType.hpp"

static const std::map<std::string, std::string> type_to_symbol = {
    {"USD", USD},
    {"EURO", EURO},
    {"STERLING", STERLING},
    {"PERCENTAGE", PERCENT_SYMBOL},
    {"RAW_NUMBER", RAW_NUMBER}};
static const std::map<std::string, std::string> symbol_to_type = {
    {USD, "USD"},
    {EURO, "EURO"},
    {STERLING, "STERLING"},
    {PERCENT_SYMBOL, "PERCENTAGE"},
    {RAW_NUMBER, "RAW_NUMBER"}};

class NumericTypeMapping
{
public:
    static std::string get_symbol(std::string format)
    {
        return type_to_symbol.at(format);
    }

    static std::string get_format(std::string symbol)
    {
        return symbol_to_type.at(symbol);
    }
};

bool is_number(const std::string &s);
bool is_float(const std::string &s);
bool is_currency(const std::string &s);
bool is_currency(const std::string &s);
bool is_percent(const std::string &s);
long double parse_number(std::string *str, DataPattern *pattern);
std::string remove_currency(std::string *str_num);
std::string remove_percentage(std::string *str_num);
std::string get_numeric_type(std::string *str);
std::string remove_non_numeric(std::string *str, bool include_decimal);

#endif
