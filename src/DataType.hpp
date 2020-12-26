#ifndef DATA_TYPE_H
#define DATA_TYPE_H

enum DataType
{
    NUMBER,
    STRING,
    DATE,
    FLOAT
};

static const DataType data_types[4] = {DataType::NUMBER, DataType::STRING, DataType::DATE, DataType::FLOAT};

#endif
