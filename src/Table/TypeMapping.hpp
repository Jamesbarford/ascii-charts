#ifndef TYPE_MAPPING_CLASS
#define TYPE_MAPPING_CLASS

#include <string>
#include <map>
#include <vector>

#include "../DataType.hpp"

struct TypeMap
{
	DataType type;
	PatternHex hex;
};

class TypeMapping
{
public:
	static TypeMapping create(std::vector<std::string>);
	void insert(std::string, TypeMap);
	bool has(std::string key);
	TypeMap get(std::string &key);

private:
	std::string valid_types = "string, number, date";
	std::map<std::string, TypeMap> current_type_mapping;
};

#endif
