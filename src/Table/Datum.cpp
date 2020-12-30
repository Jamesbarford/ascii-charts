#include <iostream>
#include <iomanip>
#include <sstream>

#include "../DataType.hpp"
#include "../formatters/date_formatter.hpp"
#include "Datum.hpp"

bool Datum::query(std::function<bool(Entry)> predicate)
{
	return predicate(this->data);
}

void Datum::insert(Entry data, DataType type)
{
	this->data = data;
	this->type = type;
}

std::string Datum::get_raw()
{
	switch (type)
	{
	case DataType::_NUMBER:
		return std::to_string(std::get<long long>(data));
	case DataType::_STRING:
		return std::get<std::string>(data);
	case DataType::_DATE:
		return std::to_string(std::get<long>(data));
	case DataType::_FLOAT:
	{
		long double d = std::get<long double>(data);
		std::ostringstream formatted;
		formatted << d;
		return formatted.str();
	}
	default:
		break;
	}
}

std::string Datum::to_string()
{
	switch (type)
	{
	case DataType::_NUMBER:
		return std::to_string(std::get<long long>(data));
	case DataType::_STRING:
		return std::get<std::string>(data);
	case DataType::_DATE:
		return to_date_string(std::get<long>(data), "%Y-%m-%dT%H:%M:%SZ");
	case DataType::_FLOAT:
		return std::to_string(std::get<long double>(data));
	default:
		break;
	}
}
