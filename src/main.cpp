#include <iostream>
#include <string>
#include <variant>

#include "Table/Table.hpp"
#include "util/CommandMap.hpp"
#include "Table/Datum.hpp"

int main(int argc, char *argv[])
{
	CommandMap command_map = create_command_map(argc, argv);
	std::string path = command_map.at(PATH).at(0);

	Table table = Table::from_csv(path);

	table.db.connect();
	table.db.exec_print("SELECT COUNT (*) AS total FROM test_table;");
	table.db.close();

	table.db.connect();
	table.db.exec_no_callback("DROP TABLE test_table;");
	table.db.close();
}
