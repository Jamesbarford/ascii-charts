/**
 * decimals -> 1.20
 * percentage -> 4.50%
 * currency -> £4.50, $1,000,000
 */
#include <iomanip>
#include <iostream>
#include <sstream>

#include "../util/string_util.hpp"
#include "numeric_parser.hpp"

std::string _get_numeric_type(std::string *str, char const **tokens);

long double parse_number(std::string *str, DataPattern *pattern)
{
    if (pattern->compare("USD") == 0 || pattern->compare("EURO") == 0 || pattern->compare("STERLING") == 0)
        return std::stold(remove_currency(str));
    if (pattern->compare("PERCENTAGE"))
        return std::stold(remove_percentage(str));
    return std::stold(remove_non_numeric(str, INCLUDE_DECIMAL));
}

std::string get_numeric_type(std::string *str)
{
    char const *all_symbols[5] = {EURO, USD, STERLING, PERCENT_SYMBOL, NULL_TERMINATING_STRING};
    return _get_numeric_type(str, all_symbols);
}

bool is_currency(const std::string &s)
{
    std::string tmp = std::string(s);
    char const *currency_symbols[4] = {EURO, USD, STERLING, NULL_TERMINATING_STRING};
    if (!some_match(&tmp, (char **)currency_symbols))
        return false;

    std::string sanitized = remove_currency(&tmp);

    return is_number(sanitized) || is_float(sanitized);
}

bool is_percent(const std::string &s)
{
    std::string tmp = std::string(s);
    if (!string_contains(&tmp, PERCENT_SYMBOL))
        return false;
    std::string sanitized = remove_percentage(&tmp);

    return is_number(sanitized) || is_float(sanitized);
}

bool is_number(const std::string &s)
{
    auto predicate = [](unsigned char c) -> bool {
        return !std::isdigit(c);
    };

    return !s.empty() && std::find_if(s.begin(), s.end(), predicate) == s.end();
}

bool is_float(const std::string &s)
{
    if (s.empty())
        return false;
    std::string tmp = std::string(s);

    if (!string_contains(&tmp, DECIMAL_DELIMITER))
        return false;

    try
    {
        std::stold(s);
        return true;
    }
    catch (...)
    {
        return false;
    }

    return false;
}

std::string remove_percentage(std::string *str_num)
{
    return get_ascii_between(str_num, [](char c) -> bool {
        return c != ASCII_PERCENT && c != ASCII_COMMA;
    });
}

std::string remove_currency(std::string *str_num)
{
    return get_ascii_between(str_num, ASCII_NUMERIC_START, ASCII_NUMERIC_END, ASCII_DECIMAL);
}

/* This feels a bit fragile */
std::string _get_numeric_type(std::string *str, char const **tokens)
{
    std::vector<std::string> found_tokens = StringSanitizer(*str).get_tokens((char **)tokens);
    if (found_tokens.size() == 0)
        return RAW_NUMBER;
    return NumericTypeMapping::get_format(found_tokens.at(0));
}

std::string remove_non_numeric(std::string *str, bool include_decimal)
{
    if (include_decimal)
        return get_ascii_between(str, ASCII_NUMERIC_START, ASCII_NUMERIC_END, ASCII_DECIMAL);
    return get_ascii_between(str, ASCII_NUMERIC_START, ASCII_NUMERIC_END);
}