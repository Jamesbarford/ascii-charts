#ifndef DATE_PARSER_H
#define DATE_PARSER_H

#define NULL_DATE_PATTERN "NOT_FOUND"
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
    "%d/%m/%Y %H:%M:%S",
    "%d/%m/%Y %H:%M",
    "%d/%m/%Y %I:%M %p",
    "%m/%d/%Y %I:%M%p",
    "%b %e, %Y %I:%M %p",
});

static const std::vector<std::string> date_patterns({
    "%d/%m/%y",
    "%Y/%m/%d",
    "%d/%m/%Y",
    "%d %b %Y",
    "%b %d, %Y",
    "%d-%b-%y",
    "%Y-%m-%d",
    "%Y-%m",
    "%m/%d/%Y",
});

#endif
