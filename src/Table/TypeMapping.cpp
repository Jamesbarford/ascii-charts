#include <string>
#include <map>

#include "../DataType.hpp"
#include "TypeMapping.hpp"

void TypeMapping::insert(std::string key, TypeMap type_map)
{
	current_type_mapping.insert({key, type_map});
}

bool TypeMapping::has(std::string key)
{
	if (current_type_mapping.find(key) != current_type_mapping.end())
		return true;
	return false;
}

TypeMap TypeMapping::get(std::string &key)
{
	if (!has(key))
		throw std::invalid_argument("No mapping for key : " + key);
	return current_type_mapping.at(key);
}
