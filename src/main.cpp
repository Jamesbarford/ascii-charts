#include <iostream>

#include "csv_tokenizer.hpp"
#include "Table.hpp"
#include "parser.hpp"

int main(void)
{
    Table table = Table::from_csv("./test-csv/test.csv");

    table.print([](TableRow r) -> void {
        for (auto rr : r)
           rr.print();
        std::cout << '\n';
    });
}
