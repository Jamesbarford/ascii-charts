#include <iostream>
#include "db.hpp"
#include "QueryStream.hpp"

void DB::connect()
{
	int exit = 0;
	// TODO: intantiate with non-debug
	exit = sqlite3_open("./db/test/test.db", &this->db);
	if (exit)
		std::cerr << "Error open DB " << sqlite3_errmsg(this->db) << std::endl;
}

void DB::close()
{
	sqlite3_close(this->db);
}

void DB::exec_no_callback(std::string const &query)
{
	this->exec(query, nullptr);
}

void DB::exec(std::string const &query, sqlite3_callback cb)
{
	int rc = 0;
	char *error_msg;

	rc = sqlite3_exec(this->db, query.c_str(), cb, 0, &error_msg);
	if (rc != SQLITE_OK)
	{
		std::cerr << "SQL error: " << error_msg << '\n';
		sqlite3_free(error_msg);
	}
}

void DB::exec_print(std::string const &query)
{
	this->exec(query, [](void *NotUsed, int argc, char **argv, char **azColName) -> int {
		int i;
		for (i = 0; i < argc; i++)
			std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL");

		std::cout << "\n";
		return 0;
	});
}

void DB::create_table(std::string const &table_name, std::string const &query)
{
	QueryStream qs;

	qs << "CREATE TABLE " << table_name << "(" << query << ");\n";

	exec_no_callback(qs.get_sanitized_query());
}

void DB::insert(std::string const &table_name, std::string const &query)
{
	QueryStream qs;

	qs << "INSERT INTO " << table_name << " VALUES\n" << query;

	exec_no_callback(qs.get_sanitized_query());
}
