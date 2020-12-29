#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

#include "date_parser.hpp"
#include "numeric_parser.hpp"

std::string get_milliseconds(std::string date_string);

bool is_date(std::string date_string)
{
    return get_date_pattern(date_string) != NULL_DATE_PATTERN;
}

std::string get_date_pattern(std::string date_string)
{
    std::string pattern = get_date_pattern(date_string, &date_time_patterns);
    if (pattern == NULL_DATE_PATTERN)
        pattern = get_date_pattern(date_string, &date_patterns);
    return pattern;
}

// brute force find a match.
std::string get_date_pattern(std::string date_string, const std::vector<std::string> *patterns)
{
    std::tm t = {};
    std::string pattern = NULL_DATE_PATTERN;

    for (size_t i = 0; i < patterns->size(); ++i)
    {
        std::istringstream ss(date_string);
        pattern = patterns->at(i);
        ss >> std::get_time(&t, pattern.c_str());

        if (ss.fail())
        {
            pattern = NULL_DATE_PATTERN;
            continue;
        }
        else
            return pattern;
    }

    return pattern;
}

long parse_date(std::string date_string)
{
    std::string pattern = get_date_pattern(date_string);

    if (pattern == NULL_DATE_PATTERN)
        return NULL_DATE_EPOCH;

    return parse_date(date_string, pattern);
}

long parse_date(std::string date_string, std::string pattern)
{
    std::tm t = {};
    std::istringstream ss(date_string);

    ss >> std::get_time(&t, pattern.c_str());

    std::chrono::milliseconds time(mktime(&t));
    size_t time_in_seconds = time.count();

    if (ss.fail() || time_in_seconds == NULL_DATE_EPOCH)
        return NULL_DATE_EPOCH;

    return std::stol(std::to_string(time.count()).append(get_milliseconds(date_string)));
}

/* this is a bit fragile */
std::string get_milliseconds(std::string date_string)
{
    if (!is_date_time(&date_string))
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
            if (!is_number(millisecond_str) || millisecond_str.size() != 3)
                millisecond_str = NULL_MILLISECONDS;
            else
                break;
        }
    }

    return !is_number(millisecond_str) ? NULL_MILLISECONDS : millisecond_str;
}
