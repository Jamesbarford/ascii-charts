#include <string>
#include <vector>
#include <iostream>
#include <fstream>

const std::string CSV_DELIMITER = ",";

void traverse_csv(std::string path, std::function<void(std::string csv_string, size_t row)> iteratee)
{
    size_t row = 0;
    std::ifstream infile(path);
    std::string csv_string;

    while (std::getline(infile, csv_string))
    {
        iteratee(csv_string, row);
        row++;
    }

    infile.close();
}

void split_row(std::string csv_string, std::function<void(std::string row_item, size_t column_idx)> iteratee)
{
    size_t pos = 0;
    size_t column_idx = 0;


    while ((pos = csv_string.find(CSV_DELIMITER)) != std::string::npos)
    {
        iteratee(csv_string.substr(0, pos), column_idx);
        csv_string.erase(0, pos + CSV_DELIMITER.length());
        ++column_idx;
    }

    column_idx = 0;
}
