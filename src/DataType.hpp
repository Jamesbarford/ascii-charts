#ifndef DATA_TYPE_H
#define DATA_TYPE_H

enum DataType
{
    NUMBER,
    STRING,
    DATE
};

static const DataType data_types[3] = {DataType::NUMBER, DataType::STRING, DataType::DATE};

#endif
