#ifndef DATE_PARSER_H
#define DATE_PARSER_H

#define NULL_DATE_PATTERN "NULL_DATE_PATTERN"
#define NULL_MILLISECONDS "000"
#define NULL_DATE_EPOCH -1

#include <vector>
#include <string>

bool is_date(std::string date_string);
long parse_date(std::string date_string);
long parse_date(std::string date_string, std::string pattern);
std::string get_date_pattern(std::string date_string, const std::vector<std::string> *patterns);
std::string get_date_pattern(std::string date_string);

static const std::vector<std::string> date_time_patterns({
    "%Y-%m-%dT%H:%M:%SZ",
    "%Y-%m-%dT%H:%M:%S",
    "%Y-%m-%d %H:%M:%S",
    "%Y/%m/%dT%H:%M:%SZ",
    "%Y/%m/%dT%H:%M:%S",
    "%Y/%m/%d %H:%M:%S",
    "%d/%m/%Y %H:%M:%S",
    "%d/%m/%Y %H:%M",
    "%d/%m/%Y %I:%M %p",
    "%m/%d/%Y %I:%M%p",
    "%d-%m-%Y %H:%M:%S",
    "%d-%m-%Y %H:%M",
    "%d-%m-%Y %I:%M %p",
    "%m-%d-%Y %I:%M%p",
    "%b %e, %Y %I:%M %p",
});

static const std::vector<std::string> date_patterns({
    "%Y/%m/%d",
    "%d/%m/%y",
    "%d/%m/%Y",
    "%m/%d/%Y",
    "%Y/%m",
    "%d/%b/%y",
    "%Y-%m-%d",
    "%d-%b-%y",
    "%d-%m-%y",
    "%d-%m-%Y",
    "%m-%d-%Y",
    "%d-%b-%y",
    "%Y-%m",
    "%d %b %Y",
    "%b %d, %Y",
});

static bool is_date_time(std::string *pattern)
{
    for (auto p : date_time_patterns)
        if (pattern->compare(p) == 0)
            return true;
    return false;
}

#endif
