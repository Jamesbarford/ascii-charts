#ifndef TABLE_CLASS
#define TABLE_CLASS

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>

#include "../Collection.hpp"
#include "../DataType.hpp"
#include "../parsers/parser.hpp"
#include "../repository/db.hpp"
#include "TypeMapping.hpp"
#include "Datum.hpp"

class Table : public Collection<std::vector<Datum>, Datum>
{
public:
	TypeMapping type_mapping;
	DB db;
	std::string table_name;
	Table(std::string const &name)
	{
		table_name = name;
	}
	static Table from_csv(std::string path);
	virtual Datum converter(std::string raw, int column_idx)
	{
		std::string header = this->headers.at(column_idx);
		TypeMap type_map = this->type_mapping.get(header);
		return create_datum(&raw, type_map.type, type_map.hex);
	}

private:
	std::vector<Datum> current_row;
};

#endif
