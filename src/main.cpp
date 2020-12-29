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

	table.peek(200, [](Datum d) {
		return d.to_string();
	});
}
