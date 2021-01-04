#include "QueryStream.hpp"

QueryStream &QueryStream::operator<<(std::string const &value)
{
	query << value;
	return *this;
}

QueryStream &QueryStream::operator<<(char const &value)
{
	query << value;
	return *this;
}

std::string QueryStream::get_sanitized_query()
{
	std::string sql_query = query.str();
	size_t i = sql_query.size() - 1;

	char c = '\0';

	for (; i > 0; --i)
	{
		c = sql_query.at(i);
		if (c == ';')
			break;

		if (c == ',')
		{
			sql_query.at(i) = ';';
			break;
		}
	}

	return sql_query;
}

void QueryStream::clear()
{
	query.clear();
}
