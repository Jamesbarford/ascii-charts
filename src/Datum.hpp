#ifndef DATUM
#define DATUM

#include <string>
#include <variant>

#include "TypeDefs.hpp"

typedef std::variant<std::string, long double, long> Entry;

class Datum
{
public:
    void print();
    bool query(std::function<bool(Entry)> predicate);
    void insert(Entry data, DATA_TYPE type);
    std::string to_string();

private:
    Entry data;
    DATA_TYPE type;
};

#endif
