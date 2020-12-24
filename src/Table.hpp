#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <map>
#include <string>

#include "TypeMapping.hpp"
#include "Datum.hpp"

typedef std::vector<Datum> TableRow;

class Table
{
public:
    static Table from_csv(std::string path);
    void insert(TableRow);
    void insert(std::vector<TableRow>);
    void collect(std::string, int);
    void print(void (*iteratee)(TableRow));
    int size();
    void set_headers(std::map<int, std::string>*);
    std::vector<TableRow> select(bool (*predicate)(TableRow));
    std::map<int, std::string> headers;
    std::vector<TableRow> data;
    TableRow select_single(bool (*predicate)(TableRow));
    TypeMapping type_mapping;

private:
    TableRow current_row;
};

#endif
