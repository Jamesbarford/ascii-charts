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

long double parse_number(std::string *str, PatternHex pattern)
{
	if (_is_currency(pattern))
		return std::stold(remove_currency(str));
	if (_is_percentage(pattern))
		return std::stold(remove_percentage(str));
	return std::stold(remove_non_numeric(str));
}

PatternHex get_numeric_type(std::string *str)
{
	return _get_numeric_type(str, numeric_symbols);
}

bool is_currency(const std::string &s)
{
	std::string tmp = std::string(s);
	if (!some_match(&tmp, currency_symbols))
		return false;

	std::string sanitized = remove_currency(&tmp);

	return is_integer(sanitized) || is_float(sanitized);
}

bool is_percent(const std::string &s)
{
	std::string tmp = std::string(s);
	if (!string_contains(&tmp, SYMBOL_PERCENT))
		return false;
	std::string sanitized = remove_percentage(&tmp);

	return is_integer(sanitized) || is_float(sanitized);
}

bool is_integer(const std::string &s)
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

	if (!string_contains(&tmp, ASCII_DECIMAL))
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

PatternHex _get_numeric_type(std::string *str, std::vector<std::string> tokens)
{
	std::vector<std::string> found_tokens = find_tokens(str, tokens);
	if (found_tokens.size() == 0)
	{
		if (string_contains(str, ASCII_DECIMAL))
			return NumericType::FLOAT;
		return is_strnum(str);
	}
	return symbol_to_numeric_type.at(found_tokens.at(0));
}

std::string remove_non_numeric(std::string *str)
{
	return get_ascii_between(str, ASCII_NUMERIC_START, ASCII_NUMERIC_END);
}
