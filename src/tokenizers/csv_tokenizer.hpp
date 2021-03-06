#ifndef CSV_TOKENIZER_H
#define CSV_TOKENIZER_H

#include <string>
#include <functional>

void traverse_csv(std::string path, std::function<void(std::string csv_string, size_t row)> iteratee);
void split_row(std::string csv_string, std::function<void(std::string row_item, size_t column_idx)>);
void csv_reader(std::string path, std::function<void(size_t row_idx, size_t column_idx, std::string value)> iteratee);

#endif
