#include <iostream>
#include <string>
#include <variant>
#include "./external/datum_parser.hpp"
#include "util/CommandMap.hpp"

int main(int argc, char *argv[])
{

	datum::Datum d = datum::parse("2020/09/09");

	d.visit<unsigned long>([](auto e) { std::cout << e << '\n'; });


	// CommandMap command_map = create_command_map(argc, argv);
	// std::string path = command_map.at(PATH).at(0);

	// Table table = Table::from_csv(path);

	// table.db.connect();
	// table.db.exec_print("SELECT COUNT (*) AS total FROM test_table;");
	// table.db.close();

	// table.db.connect();
	// table.db.exec_no_callback("DROP TABLE test_table;");
	// table.db.close();
}
