#ifndef NUMERIC_PARSER_H
#define NUMERIC_PARSER_H

#define EURO "€"
#define USD "$"
#define STERLING "£"

#define DECIMAL_DELIMITER '.'
#define PERCENT_SYMBOL "%"

#define NULL_CURRENCY "not a currency"
#define NULL_PERCENT "not a percent"

#include "../util/string_util.hpp"

static const char *CURRENCY_SYMBOLS[4] = {EURO, USD, STERLING, "\0"};
static const char *PERCENT_SYMBOLS[2] = {PERCENT_SYMBOL, "\0"};

bool is_number(const std::string &s);
bool is_float(const std::string &s);
bool is_currency(const std::string &s);
bool is_currency(const std::string &s);
bool is_percent(const std::string &s);
std::string remove_symbols(std::string *str, char **symbols, std::string fallback);
std::string remove_currency(std::string *str_num);
std::string remove_percentage(std::string *str_num);
std::string remove_decimals(std::string *str_num);

#endif
