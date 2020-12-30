#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <string>
#include <map>
#include <vector>

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

#define is_invalid_date_pattern(x) (x == INVALID_DATE)
#define is_invalid_number_pattern(x) (x == INVALID_NUMBER)
#define is_invalid_float_pattern(x) (x == INVALID_FLOAT)

#define is_date_time_pattern(x) (x >= DateType::F01 && x <= DateType::F015)
#define is_date_pattern(x) (x >= DateType::F01 && x <= DateType::F030)

#define is_string_pattern(x) (x == StringTypes::STRING)

#define is_numeric(x) (x >= NumericType::INTEGER && x <= NumericType::FLOAT)
#define is_integer_pattern(x) (x == NumericType::INTEGER)
#define is_percentage_pattern(x) (x == NumericType::PERCENTAGE)
#define is_float_pattern(x) (x >= NumericType::PERCENTAGE && x <= NumericType::FLOAT)
#define is_currency_pattern(x) (x >= NumericType::USD && x <= NumericType::EURO)

#define valid_data_type(x) (is_integer_pattern(x) || is_string_pattern(x) || is_date_pattern(x) || is_float_pattern(x))

#define UNKNOWN_TYPE -1

typedef signed int PatternHex;

enum DataType
{
	_NUMBER,
	_STRING,
	_DATE,
	_FLOAT
};

extern const std::vector<DataType> data_types;

// NUMERIC
enum NumericType
{
	INTEGER = 0x10,
	PERCENTAGE,
	USD,
	GPB,
	EURO,
	FLOAT
};

extern const std::map<std::string, PatternHex> symbol_to_numeric_type;
extern const std::vector<PatternHex> int_options;
extern const std::vector<PatternHex> float_options;
extern const std::vector<std::string> numeric_symbols;
extern const std::vector<std::string> currency_symbols;

// STRINGS
enum StringType
{
	STRING = 0x20
};
extern const std::vector<PatternHex> string_options;

// DATES
enum DateType
{
	F01 = 0x30,
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

extern const std::vector<PatternHex> all_date_time_options;
extern const std::vector<PatternHex> date_time_options;
extern const std::vector<PatternHex> date_options;
extern const std::map<PatternHex, std::string> hex_to_date_pattern;
extern const std::map<std::string, PatternHex> date_pattern_to_hex;

extern std::vector<PatternHex> data_type_options(DataType &type);
extern DataType hex_to_data_type(PatternHex h);

#endif /* DATA_TYPE_H */
