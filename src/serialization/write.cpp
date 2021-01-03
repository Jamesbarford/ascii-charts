#include "serialization.hpp"

void _write_to_hex(std::ofstream *hex_dump, char character, size_t &pos);

void table_json_dump(Table *table)
{
	std::ofstream json_dump;
	std::vector<std::vector<Datum>> *data = table->get_data();
	size_t width = 0;
	size_t data_size = data->size();
	size_t row_size = table->headers.size();

	json_dump.open("json_dump_1.json");
	json_dump << "[";

	for (std::vector<Datum> row : *data)
	{
		--data_size;
		json_dump << "{";
		for (Datum d : row)
		{
			size_t header_key = width % row_size;
			std::string header = table->headers.at(header_key);
			std::string data = d.get_raw();
			TypeMap t = table->type_mapping.get(header);

			json_dump << "\""
					  << header
					  << "\":"
					  << ((is_numeric(t.hex) || is_date_pattern(t.hex)) ? data : "\"" + data + "\"")
					  << (header_key != row_size - 1 ? "," : "");
			width++;
		}

		json_dump << "}"
				  << (data_size != 0 ? "," : "");
	}

	json_dump << "]";
	json_dump.close();
}

void table_csv_dump(Table *table)
{
	std::ofstream csv_dump;
	size_t width = 1;
	size_t row_size = table->headers.size();
	csv_dump.open("csvdump_1.csv");

	for (auto header : table->headers)
	{
		csv_dump << header.second << (width % row_size == 0 ? "" : ",");
		++width;
	}
	csv_dump << "\n";

	for (std::vector<Datum> row : *table->get_data())
	{
		for (Datum d : row)
		{
			csv_dump << d.get_raw() << (width % row_size == 0 ? "" : ",");
			width++;
		}
		csv_dump << "\n";
	}

	csv_dump.close();
}

void table_hex_dump(Table *table)
{
	std::ofstream hex_dump;
	size_t i = 0;
	std::vector<std::vector<Datum>> *data = table->get_data();
	hex_dump.open("hexdump_1");

	for (std::vector<Datum> row : *data)
	{
		for (Datum d : row)
		{
			for (unsigned char c : d.get_raw())
			{
				_write_to_hex(&hex_dump, c, i);
			}
			_write_to_hex(&hex_dump, ',', i);
		}
		_write_to_hex(&hex_dump, '\n', i);
	}

	while ((i++ % 16) != 0)
		hex_dump << "   ";

	hex_dump << "  \n";
	hex_dump.close();
}

void _write_to_hex(std::ofstream *hex_dump, char character, size_t &pos)
{
	if ((pos % 16) == 0)
	{
		if (pos != 0)
		{
			*hex_dump << " \n";
		}
		*hex_dump << std::hex
				  << std::setfill('0')
				  << std::setw(8)
				  << pos
				  << " ";
	}
	*hex_dump << " "
			  << std::hex
			  << std::setfill('0')
			  << std::setw(2)
			  << (int)character;
	pos++;
}
