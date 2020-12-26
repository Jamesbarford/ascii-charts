#include <iostream>
#include <iomanip>

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

std::string Datum::to_string()
{
    switch (type)
    {
    case DataType::NUMBER:
        return std::to_string(std::get<long double>(data));
    case DataType::STRING:
        return std::get<std::string>(data);
    case DataType::DATE:
        return to_date_string(std::get<long>(data), "%Y-%m-%dT%H:%M:%SZ");
    default:
        break;
    }
}