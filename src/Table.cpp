#include <vector>
#include <string>
#include <iostream>
#include <chrono>

#include "Table.hpp"
#include "TypeMapping.hpp"
#include "Sampler.hpp"
#include "Timer.hpp"
#include "csv_tokenizer.hpp"
#include "parser.hpp"

void Table::insert(std::vector<TableRow> rows)
{
    for (auto row : rows)
        this->insert(row);
}

void Table::insert(TableRow row)
{
    data.push_back(row);
}

void Table::collect(std::string row_item, int column_idx)
{
    std::string header = this->headers.at(column_idx);
    DATA_TYPE type = this->type_mapping.get(header);
    Datum d = create_datum(row_item, type);

    if (column_idx + 1 == this->headers.size())
    {
        this->current_row.push_back(d);
        this->data.push_back(this->current_row);
        this->current_row.clear();
    }
    else
        this->current_row.push_back(d);
}

void Table::set_headers(std::map<int, std::string> *headers)
{
    for (auto [key, value] : *headers)
        this->headers.insert({key, value});
}

Table Table::from_csv(std::string path)
{
    Table table;
    Sampler sampler;
    Timer timer = Timer("Table creation");

    timer.start();

    traverse_csv(path, [&sampler, &table](std::string row, size_t row_idx) -> void {
        TableRow table_row;

        split_row(row, [&sampler, &row_idx, &table](std::string row_item, int column_idx) -> void {
            if (row_idx == 0)
                sampler.collect_headers(row_item, column_idx);
            else
            {
                if (sampler.get_size() > 100)
                    table.collect(row_item, column_idx);
                if (sampler.get_size() < 100)
                    sampler.collect(row_item, column_idx);
                if (sampler.get_size() == 100)
                {
                    table.type_mapping = sampler.to_type_mapping();
                    table.headers = sampler.headers;
                    for (auto d : *sampler.get_sample_data())
                        table.insert(create_datum_vector(&d, &table.headers, &table.type_mapping));
                    sampler.collect(row_item, column_idx);
                }
            }
        });
    });

    timer.end();

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
