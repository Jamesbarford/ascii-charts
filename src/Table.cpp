#include <vector>
#include <string>
#include <iostream>

#include "Table.hpp"
#include "csv_tokenizer.hpp"
#include "Sampler.hpp"
#include "parser.hpp"
#include "TypeMapping.hpp"

void Table::insert(std::vector<TableRow> rows)
{
    for (auto row : rows)
        this->insert(row);
}

void Table::insert(TableRow row)
{
    data.push_back(row);
}

void Table::set_headers(std::vector<std::string> headers)
{
    this->headers = headers;
}

Table Table::from_csv(std::string path)
{
    Table table;
    Sampler sampler;

    traverse_csv(path, [&sampler, &table](std::string row, size_t row_idx) -> void {
        TableRow table_row;

        split_row(row, [&sampler, &row_idx, &table](std::string row_item, int column_idx) -> void {
            if (row_idx == 0)
            {
                sampler.collect_headers(row_item, column_idx);
                table.headers.push_back(row_item);
                std::cout << row_item << '\n';
            }
            else
                sampler.collect(row_item, column_idx);
            // table_row.push_back(row_item);
        });

        if (row_idx >= 1)
        {

            // table.insert(table_row);
        }
    });

    sampler.print_headers();
    TypeMapping type_mapping = sampler.to_type_mapping();
    std::vector<SampleData> *s = sampler.get_parsed_data();
    for (auto d : *s)
    {
        table.insert(create_datum_vector(&d, &sampler.headers, &type_mapping));
    }

    return table;
}

std::vector<TableRow> Table::select(bool (*predicate)(TableRow row))
{
    std::vector<TableRow> rows;

    for (auto row : data)
        if (predicate(row))
            rows.push_back(row);

    return rows;
}

TableRow Table::select_single(bool (*predicate)(TableRow))
{
    for (auto row : data)
        if (predicate(row))
            return row;

    return TableRow();
}

void Table::print(void (*iteratee)(TableRow row))
{
    for (auto row : data)
        iteratee(row);
}

int Table::size()
{
    return this->data.size();
}
