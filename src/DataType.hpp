#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <string>
#include <map>

#define ASCII_NUMERIC_START 48
#define ASCII_NUMERIC_END 57
#define ASCII_DECIMAL 46
#define ASCII_PERCENT 37
#define ASCII_COMMA 44

// The £ signs falls outside of the ASCII scale, so for consistency treat all as strings
#define SYMBOL_EURO "€"
#define SYMBOL_USD "$"
#define SYMBOL_STERLING "£"
#define SYMBOL_PERCENT "%"

#define NULL_STRING_POSITION std::string::npos
#define NULL_MILLISECONDS "000"
#define NULL_TERMINATING_STRING "\0"
#define NULL_TERMINATING_CHAR '\0'
#define NULL_DATE_EPOCH -1

#define INVALID_DATE 0xF0030
#define INVALID_NUMBER 0xF0031
#define INVALID_FLOAT 0xF0032
#define INVALID_TYPE 0xF1111

#define is_invalid_date(x) (x == INVALID_DATE)
#define is_invalid_number(x) (x == INVALID_NUMBER)
#define is_invalid_float(x) (x == INVALID_FLOAT)

#define is_date_time(x) (x >= DateType::F01 && x <= DateType::F015)
#define _is_date(x) (x >= DateTypes::F01 && x <= DateTypes::F030)

#define _is_string(x) (x == StringTypes::STRING)

#define _is_integer(x) (x == NumericType::INTEGER)
#define _is_percentage(x) (x == NumericType::PERCENTAGE)
#define _is_float(x) (x >= NumericType::PERCENTAGE && <= NumericType::FLOAT)
#define _is_currency(x) (x >= NumericType::USD && x <= NumericType::EURO)

#define valid_data_type(x) (_is_number(x) || _is_string(x) || _is_date(x) || _is_float(x))

#define UNKNOWN_TYPE -1

typedef std::string DataPattern;
typedef signed int Hex;

enum DataType
{
	_NUMBER,
	_STRING,
	_DATE,
	_FLOAT
};

static const DataType data_types[4] = {DataType::_NUMBER, DataType::_STRING, DataType::_DATE, DataType::_FLOAT};

// NUMERIC
enum NumericType
{
	INTEGER = 0x00010,
	PERCENTAGE,
	USD,
	GPB,
	EURO,
	FLOAT
};

static const std::map<std::string, Hex> symbol_to_numeric_type = {
	{SYMBOL_PERCENT, NumericType::PERCENTAGE},
	{SYMBOL_USD, NumericType::USD},
	{SYMBOL_STERLING, NumericType::GPB},
	{SYMBOL_EURO, NumericType::EURO},
};
static const int int_options[2] = {NumericType::INTEGER, NULL_TERMINATING_CHAR};
static const int float_options[6] = {NumericType::FLOAT, NumericType::PERCENTAGE, NumericType::USD, NumericType::GPB, NumericType::EURO, NULL_TERMINATING_CHAR};
static const char *numeric_symbols[6] = {SYMBOL_EURO, SYMBOL_USD, SYMBOL_STERLING, SYMBOL_PERCENT, NULL_TERMINATING_STRING};
static const char *currency_symbols[5] = {SYMBOL_EURO, SYMBOL_USD, SYMBOL_STERLING, NULL_TERMINATING_STRING};

// STRINGS
enum StringType
{
	STRING = 0x00020
};
static const int string_options[2] = {StringType::STRING, NULL_TERMINATING_CHAR};

// DATES
enum DateType
{
	F01 = 0x00030,
	F02,
	F03,
	F04,
	F05,
	F06,
	F07,
	F08,
	F09,
	F010,
	F011,
	F012,
	F013,
	F014,
	F015,
	F016,
	F017,
	F018,
	F019,
	F020,
	F021,
	F022,
	F023,
	F024,
	F025,
	F026,
	F027,
	F028,
	F029,
	F030,
};

static const int all_date_time_options[31] = {F01, F02, F03, F04, F05, F06, F07, F08, F09, F010, F011, F012, F013, F014, F015, F016, F017, F018, F019, F020, F021, F022, F023, F024, F025, F026, F027, F028, F029, F030, NULL_TERMINATING_CHAR};
static const int date_time_options[16] = {F01, F02, F03, F04, F05, F06, F07, F08, F09, F010, F011, F012, F013, F014, F015, NULL_TERMINATING_CHAR};
static const int date_options[16] = {F016, F017, F018, F019, F020, F021, F022, F023, F024, F025, F026, F027, F028, F029, F030, NULL_TERMINATING_CHAR};

static const std::map<Hex, std::string> hex_to_date_pattern = {
	{F01, "%Y-%m-%dT%H:%M:%SZ"},
	{F02, "%Y-%m-%dT%H:%M:%S"},
	{F03, "%Y-%m-%d %H:%M:%S"},
	{F04, "%Y/%m/%dT%H:%M:%SZ"},
	{F05, "%Y/%m/%dT%H:%M:%S"},
	{F06, "%Y/%m/%d %H:%M:%S"},
	{F07, "%d/%m/%Y %H:%M:%S"},
	{F08, "%d/%m/%Y %H:%M"},
	{F09, "%d/%m/%Y %I:%M %p"},
	{F010, "%m/%d/%Y %I:%M%p"},
	{F011, "%d-%m-%Y %H:%M:%S"},
	{F012, "%d-%m-%Y %H:%M"},
	{F013, "%d-%m-%Y %I:%M %p"},
	{F014, "%m-%d-%Y %I:%M%p"},
	{F015, "%b %e, %Y %I:%M %p"},
	{F016, "%Y/%m/%d"},
	{F017, "%d/%m/%y"},
	{F018, "%d/%m/%Y"},
	{F019, "%m/%d/%Y"},
	{F020, "%Y/%m"},
	{F021, "%d/%b/%y"},
	{F022, "%Y-%m-%d"},
	{F023, "%d-%b-%y"},
	{F024, "%d-%m-%y"},
	{F025, "%d-%m-%Y"},
	{F026, "%m-%d-%Y"},
	{F027, "%d-%b-%y"},
	{F028, "%Y-%m"},
	{F029, "%d %b %Y"},
	{F030, "%b %d, %Y"},
};

static int *data_type_options(DataType type)
{
	switch (type)
	{
	case DataType::_NUMBER:
		return (int *)int_options;
	case DataType::_STRING:
		return (int *)string_options;
	case DataType::_DATE:
		return (int *)all_date_time_options;
	case DataType::_FLOAT:
		return (int *)float_options;
	default:
		break;
	}
}

static DataType hex_to_data_type(Hex h)
{
	switch (h)
	{
	case NumericType::INTEGER:
		return DataType::_NUMBER;

	case NumericType::PERCENTAGE:
	case NumericType::USD:
	case NumericType::GPB:
	case NumericType::EURO:
	case NumericType::FLOAT:
		return DataType::_FLOAT;

	case DateType::F01:
	case DateType::F02:
	case DateType::F03:
	case DateType::F04:
	case DateType::F05:
	case DateType::F06:
	case DateType::F07:
	case DateType::F08:
	case DateType::F09:
	case DateType::F010:
	case DateType::F011:
	case DateType::F012:
	case DateType::F013:
	case DateType::F014:
	case DateType::F015:
	case DateType::F016:
	case DateType::F017:
	case DateType::F018:
	case DateType::F019:
	case DateType::F020:
	case DateType::F021:
	case DateType::F022:
	case DateType::F023:
	case DateType::F024:
	case DateType::F025:
	case DateType::F026:
	case DateType::F027:
	case DateType::F028:
	case DateType::F029:
	case DateType::F030:
		return DataType::_DATE;

	case StringType::STRING:
		return DataType::_STRING;

	default:
		return DataType::_STRING;
	}
}

#endif
