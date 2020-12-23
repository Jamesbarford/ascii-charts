#include <iostream>
#include <string>

#include "Table.hpp"
#include "CommandMap.hpp"

int main(int argc, char *argv[])
{
    CommandMap command_map = create_command_map(argc, argv);
    std::string path = command_map.at(PATH).at(0);

    Table table = Table::from_csv(path);

    table.print([](TableRow r) -> void {
        for (auto rr : r)
            rr.print();
        std::cout << '\n';
    });
}
