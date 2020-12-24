#include <iostream>
#include <iomanip>

#include "../util/overload.hpp"
#include "../DataType.hpp"
#include "Datum.hpp"

void Datum::print()
{
    std::visit(
        overload{
            [](long arg) -> void { std::cout << arg << ' '; },
            [](long double arg) -> void { std::cout << std::fixed << arg << ' '; },
            [](std::string arg) -> void { std::cout << std::quoted(arg) << ' '; },
        },
        data);
}

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
        return std::to_string(std::get<long>(data));
    default:
        break;
    }
}