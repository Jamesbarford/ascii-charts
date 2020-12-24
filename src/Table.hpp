#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <map>
#include <string>

#include "TypeMapping.hpp"
#include "Datum.hpp"
#include "Collection.hpp"
#include "parser.hpp"

class Table : public Collection<std::vector<Datum>, Datum>
{
public:
    TypeMapping type_mapping;
    static Table from_csv(std::string path);
    virtual Datum converter(std::string raw, int column_idx)
    {
        std::string header = this->headers.at(column_idx);
        DATA_TYPE type = this->type_mapping.get(header);
        return create_datum(raw, type);
    }

private:
    std::vector<Datum> current_row;
};

#endif
