#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "date_parser.hpp"
#include "../util/string_util.hpp"

bool is_date(std::string date_string)
{
	return !is_invalid_date(get_date_pattern(&date_string));
}

PatternHex get_date_pattern(std::string *date_string)
{
	PatternHex pattern = get_date_pattern(date_string, date_time_options);
	if (is_invalid_date(pattern))
		pattern = get_date_pattern(date_string, date_options);
	return pattern;
}

PatternHex get_date_pattern(std::string *date_string, std::vector<PatternHex> patterns)
{
	std::tm t = {};

	for (PatternHex opt : patterns)
	{
		std::istringstream ss(*date_string);
		ss >> std::get_time(&t, hex_to_date_pattern.at(opt).c_str());

		if (ss.fail())
			continue;
		else
			return opt;
	}

	return INVALID_DATE;
}

long parse_date(std::string *date_string)
{
	PatternHex pattern = get_date_pattern(date_string);
	if (is_invalid_date(pattern))
		return NULL_DATE_EPOCH;

	return parse_date(date_string, pattern);
}

long parse_date(std::string *date_string, PatternHex pattern)
{
	if (is_invalid_date(pattern))
		return NULL_DATE_EPOCH;

	std::string str_pattern = hex_to_date_pattern.at(pattern);
	std::tm t = {};
	std::istringstream ss(*date_string);

	ss >> std::get_time(&t, str_pattern.c_str());

	std::chrono::milliseconds time(mktime(&t));
	size_t time_in_seconds = time.count();

	if (ss.fail() || time_in_seconds == NULL_DATE_EPOCH)
		return NULL_DATE_EPOCH;

	return std::stol(std::to_string(time.count()).append(get_milliseconds(*date_string, pattern)));
}

/* this is a bit fragile */
std::string get_milliseconds(std::string date_string, PatternHex pattern)
{
	if (!is_date_time(pattern))
		return NULL_MILLISECONDS;

	char delimiters[2] = {'-', '.'};
	std::string millisecond_str = NULL_MILLISECONDS;
	size_t pos;

	for (int i = 0; i < 2; ++i)
	{
		pos = date_string.find_last_of(delimiters[i]);
		if (pos != std::string::npos)
		{
			millisecond_str = date_string.substr(pos + 1, 3);
			// reset if it was not a match
			if (!is_strnum(&millisecond_str) || millisecond_str.size() != 3)
				millisecond_str = NULL_MILLISECONDS;
			else
				break;
		}
	}

	return !is_strnum(&millisecond_str) ? NULL_MILLISECONDS : millisecond_str;
}
