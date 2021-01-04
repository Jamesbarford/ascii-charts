#ifndef QUERY_BUILDER_H
#define QUERY_BUILDER_H

#include <string>
#include <iostream>
#include <sstream>

class QueryStream
{
public:
	QueryStream &operator<<(std::string const &value);
	QueryStream &operator<<(char const &value);
	std::string get_sanitized_query();
	void clear();

private:
	std::ostringstream query;
};

#endif
