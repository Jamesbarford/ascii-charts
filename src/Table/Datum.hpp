#ifndef DATUM_CLASS
#define DATUM_CLASS

#include <string>
#include <variant>

#include "../DataType.hpp"

typedef std::variant<std::string, long double, long> Entry;

class Datum
{
public:
    void print();
    bool query(std::function<bool(Entry)> predicate);
    void insert(Entry data, DataType type);
    std::string to_string();

private:
    Entry data;
    DataType type;
};

#endif
