#include <vector>
#include <string>

#pragma once
enum DATA_TYPE
{
    NUMBER,
    STRING,
    DATE
};

static const DATA_TYPE data_types[3] = {DATA_TYPE::NUMBER, DATA_TYPE::STRING, DATA_TYPE::DATE};

#pragma once
template <class... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};

#pragma once
template <class... Ts>
overload(Ts...) -> overload<Ts...>;
