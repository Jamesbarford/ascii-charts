#include <iostream>
#include <string>

#include "Table.hpp"
#include "CommandLineArgs.hpp"

int main(int argc, char *argv[])
{
    CommandLineArgs command_args = CommandLineArgs(argc, argv);
    std::string path = command_args.at(PATH);

    Table table = Table::from_csv(path);

    table.print([](TableRow r) -> void {
        for (auto rr : r)
            rr.print();
        std::cout << '\n';
    });
}
