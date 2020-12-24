#include <vector>
#include <string>
#include <iostream>
#include <chrono>

#include "Table.hpp"
#include "Sampler.hpp"
#include "Collection.hpp"
#include "TypeMapping.hpp"
#include "Timer.hpp"
#include "csv_tokenizer.hpp"
#include "parser.hpp"

void insert_data(Sampler *sampler, Table *table, std::string raw_data, size_t row_idx, size_t column_idx);
void transfer(Sampler *sampler, Table *table);

Table Table::from_csv(std::string path)
{
    Table table;
    Sampler sampler;
    Timer timer = Timer("Table creation");

    timer.start();

    traverse_csv(path, [&sampler, &table](std::string row, size_t row_idx) -> void {
        split_row(row, [&sampler, &table, &row_idx](std::string raw_data, int column_idx) -> void {
            insert_data(&sampler, &table, raw_data, row_idx, column_idx);
        });
    });

    if (!sampler.complete)
        transfer(&sampler, &table);

    timer.end();

    return table;
}

// on the fly make a stab at guessing data types, then transfer into table
void insert_data(Sampler *sampler, Table *table, std::string raw_data, size_t row_idx, size_t column_idx)
{
    if (row_idx == 0)
        return sampler->collect_header(raw_data, column_idx);
    if (!sampler->complete && sampler->length() == 100)
    {
        sampler->complete = true;
        return transfer(sampler, table);
    }
    if (!sampler->complete)
        return sampler->collect(raw_data, column_idx);

    return table->collect(raw_data, column_idx);
}

void transfer(Sampler *sampler, Table *table)
{
    table->type_mapping = sampler->to_type_mapping();
    table->headers = sampler->headers;
    for (auto d : *sampler->get_sample_data())
        table->push_back(create_datum_vector(&d, &table->headers, &table->type_mapping));
}
