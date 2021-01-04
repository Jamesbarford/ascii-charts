#ifndef DATUM_CLASS
#define DATUM_CLASS

#include <string>
#include <variant>

#include "../DataType.hpp"

typedef std::variant<std::string, long double, long, long long> Entry;

class Datum
{
public:
	bool query(std::function<bool(Entry)> predicate);
	void insert(Entry data, DataType type);
	std::string to_string();
	std::string get_raw();

private:
	Entry data;
	DataType type;
};

#endif
