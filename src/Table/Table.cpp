#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <sstream>

#include "../Collection.hpp"
#include "../util/Timer.hpp"
#include "../util/string_util.hpp"
#include "../tokenizers/csv_tokenizer.hpp"
#include "../repository/QueryStream.hpp"
#include "Table.hpp"
#include "TypeMapping.hpp"
#include "Sampler.hpp"

void create_table(Table &table, std::string const &table_name);
void insert_data(Sampler &sampler, Table &table, QueryStream &qs, std::string raw_data, size_t row_idx, size_t column_idx);
void transfer(Sampler &sampler, Table &table);
std::string build_insert_statement(std::vector<Datum> &datum_vec, TypeMapping &type_mapping, std::map<int, std::string> &headers);

Table Table::from_csv(std::string path)
{
	Table table = Table("test_table");
	Sampler sampler = Sampler(100);
	QueryStream qs;
	Timer timer = Timer("Table creation");

	timer.start();

	table.db.connect();

	traverse_csv(path, [&](std::string row, size_t row_idx) -> void {
		split_row(row, [&](std::string raw_data, int column_idx) -> void {
			insert_data(sampler, table, qs, raw_data, row_idx, column_idx);
		});
	});

	if (!sampler.complete)
		transfer(sampler, table);
	else
		table.db.insert(table.table_name, qs.get_sanitized_query());

	timer.end();
	table.db.close();

	return table;
}

// on the fly make a stab at guessing data types, then build SQL query to insert into SQLite database
void insert_data(Sampler &sampler, Table &table, QueryStream &qs, std::string raw_data, size_t row_idx, size_t column_idx)
{
	if (row_idx == 0)
		return sampler.collect_header(raw_data, column_idx);
	if (!sampler.complete && row_idx == sampler.sample_size && (sampler.width() - 1) == column_idx)
	{
		sampler.complete = true;
		sampler.collect(raw_data, column_idx);
		return transfer(sampler, table);
	}
	if (!sampler.complete)
		return sampler.collect(raw_data, column_idx);

	table.collect(raw_data, column_idx, [&](std::vector<Datum> partial_data) -> void {
		qs << build_insert_statement(partial_data, table.type_mapping, table.headers);
	});
}

void transfer(Sampler &sampler, Table &table)
{
	QueryStream qs;
	table.type_mapping = sampler.to_type_mapping();
	table.headers = sampler.headers;

	create_table(table, table.table_name);

	for (auto d : *sampler.get_sample_data())
	{
		std::vector<Datum> datum_vec = create_datum_vector(&d, &table.headers, &table.type_mapping);
		qs << build_insert_statement(datum_vec, table.type_mapping, table.headers);
	}

	table.db.insert(table.table_name, qs.get_sanitized_query());
}

void create_table(Table &table, std::string const &table_name)
{
	std::ostringstream qs;

	for (size_t i = 0; i < table.headers.size(); ++i)
	{
		auto header = table.headers.at(i);
		qs << header << ' ' << table.type_mapping.get_sqlite_type(header) << ',';
	}

	std::string query_string = qs.str();

	table.db.create_table(table.table_name, query_string.substr(0, query_string.size() - 1));
}

std::string build_insert_statement(std::vector<Datum> &datum_vec, TypeMapping &type_mapping, std::map<int, std::string> &headers)
{
	std::string stmt = vec_to_string<Datum>(datum_vec, [&](Datum datum, size_t col_idx) -> std::string {
		std::string sql_type = type_mapping.get_sqlite_type(headers.at(col_idx));
		return (sql_type == "TEXT" ? ('\"' + datum.get_raw() + '\"') : datum.get_raw());
	});

	return "(" + stmt + "),\n";
}
