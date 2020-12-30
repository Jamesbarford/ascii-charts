#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <fstream>
#include <vector>
#include "../Table/Table.hpp"

void table_hex_dump(Table *table);
void table_csv_dump(Table *table);
void table_json_dump(Table *table);

#endif
