#include "DataType.hpp"

const std::vector<DataType> data_types = {DataType::_NUMBER, DataType::_STRING, DataType::_DATE, DataType::_FLOAT};

const std::vector<PatternHex> int_options = {NumericType::INTEGER};
const std::vector<PatternHex> float_options = {NumericType::FLOAT, NumericType::PERCENTAGE, NumericType::USD, NumericType::GPB, NumericType::EURO};
const std::vector<std::string>numeric_symbols = {SYMBOL_EURO, SYMBOL_USD, SYMBOL_STERLING, SYMBOL_PERCENT};
const std::vector<std::string>currency_symbols = {SYMBOL_EURO, SYMBOL_USD, SYMBOL_STERLING};
const std::map<std::string, PatternHex> symbol_to_numeric_type = {
	{SYMBOL_PERCENT, NumericType::PERCENTAGE},
	{SYMBOL_USD, NumericType::USD},
	{SYMBOL_STERLING, NumericType::GPB},
	{SYMBOL_EURO, NumericType::EURO},
};

const std::vector<PatternHex> string_options = {StringType::STRING};

const std::vector<PatternHex> all_date_time_options = {F01, F02, F03, F04, F05, F06, F07, F08, F09, F010, F011, F012, F013, F014, F015, F016, F017, F018, F019, F020, F021, F022, F023, F024, F025, F026, F027, F028, F029, F030};
const std::vector<PatternHex> date_time_options = {F01, F02, F03, F04, F05, F06, F07, F08, F09, F010, F011, F012, F013, F014, F015};
const std::vector<PatternHex> date_options = {F016, F017, F018, F019, F020, F021, F022, F023, F024, F025, F026, F027, F028, F029, F030};

const std::map<PatternHex, std::string> hex_to_date_pattern = {
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

std::vector<PatternHex> data_type_options(DataType &type)
{
	switch (type)
	{
	case DataType::_NUMBER:
		return int_options;
	case DataType::_STRING:
		return string_options;
	case DataType::_DATE:
		return all_date_time_options;
	case DataType::_FLOAT:
		return float_options;
	default:
		break;
	}
}

DataType hex_to_data_type(PatternHex h)
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
