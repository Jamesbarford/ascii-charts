#include <vector>
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
    void print(void (*iteratee)(TableRow));
    void set_headers(std::vector<std::string>);
    int size();
    std::vector<TableRow> select(bool (*predicate)(TableRow));
    std::vector<std::string> headers;
    std::vector<TableRow> data;
    TableRow select_single(bool (*predicate)(TableRow));
    TypeMapping type_mapping;
};
