/**
 * decimals -> 1.20
 * percentage -> 4.50%
 * currency -> £4.50
 */
#include <iomanip>
#include <iostream>
#include <sstream>

#include "../util/string_util.hpp"
#include "numeric_parser.hpp"

bool is_currency(const std::string &s)
{
    std::string tmp = std::string(s);
    if (!some_match(&tmp, (char **)CURRENCY_SYMBOLS))
        return false;

    std::string sanitized = remove_currency(&tmp);

    return is_number(sanitized) || is_float(sanitized);
}

bool is_percent(const std::string &s)
{
    std::string tmp = std::string(s);
    if (!some_match(&tmp, (char **)PERCENT_SYMBOLS))
        return false;
    std::string sanitized = remove_percentage(&tmp);

    return is_number(sanitized) || is_float(sanitized);
}

bool is_number(const std::string &s)
{
    std::string tmp = std::string(s);
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

std::string remove_decimals(std::string *str_num)
{
    return remove_seq(str_num, DECIMAL_DELIMITER);
}

std::string remove_percentage(std::string *str_num)
{
    return remove_symbols(str_num, (char **)PERCENT_SYMBOLS, NULL_PERCENT);
}

std::string remove_currency(std::string *str_num)
{
    return remove_symbols(str_num, (char **)CURRENCY_SYMBOLS, NULL_CURRENCY);
}

std::string remove_symbols(std::string *str, char **symbols, std::string fallback)
{
    std::string sanitized = fallback;
    StringSanitizer string_sanitizer = StringSanitizer(*str);
    size_t pos = string_sanitizer.find_first_pos(symbols);

    if (is_null_position(pos))
        return sanitized;

    std::vector<std::string> tokens = string_sanitizer.get_tokens(symbols);
    if (tokens.size() > 1)
        return sanitized;

    return string_sanitizer.remove_char_at(pos, tokens.at(0).size())->value();
}
