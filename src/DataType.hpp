#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <string>

enum DataType
{
    NUMBER,
    STRING,
    DATE,
    FLOAT
};

typedef std::string DataPattern;

static const DataType data_types[4] = {DataType::NUMBER, DataType::STRING, DataType::DATE, DataType::FLOAT};

#endif
