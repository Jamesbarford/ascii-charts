#include <iostream>
#include <iomanip>

#include "TypeDefs.hpp"
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

void Datum::insert(Entry data, DATA_TYPE type)
{
    this->data = data;
    this->type = type;
}