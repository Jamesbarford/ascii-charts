#ifndef SQL_DB_H
#define SQL_DB_H

#include <sqlite3.h>
#include <string>

class DB
{
public:
	void connect();
	void close();
	void exec_no_callback(std::string const &query);
	void exec(std::string const &query, sqlite3_callback cb);
	void exec_print(std::string const &query);
	void insert(std::string const &table_name, std::string const &query);
	void create_table(std::string const &table_name, std::string const &query);

private:
	sqlite3 *db;
};

#endif
