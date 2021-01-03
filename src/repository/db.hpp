#ifndef SQL_DB_H
#define SQL_DB_H

#include <sqlite3.h>
#include <string>

class DB
{
public:
	void connect();
	void close();
	void exec_no_callback(std::string &insert_statement);
	void exec(std::string &query, sqlite3_callback cb);
	void exec_print(std::string &query);

private:
	sqlite3 *db;
};

#endif
