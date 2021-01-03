#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <sstream>

#include "../Collection.hpp"
#include "../util/Timer.hpp"
#include "../util/string_util.hpp"
#include "../tokenizers/csv_tokenizer.hpp"
#include "Table.hpp"
#include "TypeMapping.hpp"
#include "Sampler.hpp"

void create_table(Table *table, std::string &table_name);
void insert_data(Sampler *sampler, Table *table, std::string raw_data, size_t row_idx, size_t column_idx);
void transfer(Sampler *sampler, Table *table);

Table Table::from_csv(std::string path)
{
	Table table;
	Sampler sampler = Sampler(100);
	Timer timer = Timer("Table creation");

	timer.start();

	table.db.connect();
	traverse_csv(path, [&sampler, &table](std::string row, size_t row_idx) -> void {
		split_row(row, [&sampler, &table, &row_idx](std::string raw_data, int column_idx) -> void {
			insert_data(&sampler, &table, raw_data, row_idx, column_idx);
		});
	});

	if (!sampler.complete)
		transfer(&sampler, &table);
	else
	{
		std::string query = table.sql_insert_statement.str();
		query.at(query.size() - 2) = ';';
		table.db.exec_no_callback(query);
	}

	timer.end();
	table.db.close();

	return table;
}

// on the fly make a stab at guessing data types, then build SQL query to insert into SQLite database
void insert_data(Sampler *sampler, Table *table, std::string raw_data, size_t row_idx, size_t column_idx)
{
	if (row_idx == 0)
		return sampler->collect_header(raw_data, column_idx);
	if (!sampler->complete && row_idx == sampler->sample_size && (sampler->width() - 1) == column_idx)
	{
		sampler->complete = true;
		sampler->collect(raw_data, column_idx);
		return transfer(sampler, table);
	}
	if (!sampler->complete)
		return sampler->collect(raw_data, column_idx);

	table->collect(raw_data, column_idx, [&](std::vector<Datum> partial_data) -> void {
		table->sql_insert_statement
			<< '('
			<< vec_to_string<Datum>(partial_data, [&](Datum datum, size_t col_idx) -> std::string {
				   std::string sql_type = table->type_mapping.get_sqlite_type(table->headers.at(col_idx));
				   return (sql_type == "TEXT" ? ('\"' + datum.get_raw() + '\"') : datum.get_raw());
			   })
			<< "),\n";
	});
}

void transfer(Sampler *sampler, Table *table)
{
	table->type_mapping = sampler->to_type_mapping();
	table->headers = sampler->headers;
	std::string table_name = "test_table";
	create_table(table, table_name);

	std::ostringstream ss;
	ss << "INSERT INTO " << table_name << " VALUES \n";
	table->sql_insert_statement << "INSERT INTO " << table_name << " VALUES \n";

	for (auto d : *sampler->get_sample_data())
	{
		std::vector<Datum> datum_vec = create_datum_vector(&d, &table->headers, &table->type_mapping);
		ss << "("
		   << vec_to_string<Datum>(datum_vec, [&](Datum datum, size_t col_idx) -> std::string {
				  std::string sql_type = table->type_mapping.get_sqlite_type(table->headers.at(col_idx));
				  return (sql_type == "TEXT" ? ('\"' + datum.get_raw() + '\"') : datum.get_raw());
			  })
		   << "),\n";
	}
	std::string query = ss.str();
	query.at(query.size() - 2) = ';';

	table->db.exec_no_callback(query);
}

void create_table(Table *table, std::string &table_name)
{
	std::ostringstream ss;

	ss << "CREATE TABLE " << table_name << "(";
	size_t i = 0;
	size_t len = table->headers.size();

	for (; i < len; ++i)
	{
		auto header = table->headers.at(i);
		std::string sql_type = table->type_mapping.get_sqlite_type(header);

		ss << header << ' ' << sql_type;

		if (i < (len - 1))
			ss << ',';
	}

	ss << ");";

	std::string query = ss.str();
	table->db.exec_no_callback(query);
}
