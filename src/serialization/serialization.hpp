#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <fstream>
#include <vector>
#include "../Table/Table.hpp"

void table_json_dump(Table *table, std::vector<std::vector<Datum>> &data);
void table_csv_dump(Table *table, std::vector<std::vector<Datum>> &data);
void table_hex_dump(std::vector<std::vector<Datum>> &data);

#endif
