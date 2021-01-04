#ifndef COLLECTION_CLASS
#define COLLECTION_CLASS

#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <map>

template <typename T, typename V>
class Collection
{
public:
	virtual V converter(std::string, int) = 0;
	std::map<int, std::string> headers;

	int length()
	{
		return data.size();
	}

	int width()
	{
		return headers.size();
	}

	void collect(std::string raw, int column_idx, std::function<void(std::vector<V> partial_data)> iteratee)
	{
		V d = converter(raw, column_idx);
		if (column_idx + 1 == width())
		{
			partial_data.push_back(d);
			iteratee(partial_data);
			partial_data.clear();
		}
		else
			partial_data.push_back(d);
	}

	void collect(std::string raw, int column_idx)
	{
		this->collect(raw, column_idx, [&](std::vector<V> partial_data) -> void {
			this->data.push_back(partial_data);
		});
	}

	void collect_header(std::string header, int column_idx)
	{
		headers.insert({column_idx, header});
	}

	void print_headers()
	{
		for (auto [column_idx, header] : headers)
			std::cout << column_idx << ": " << header << ',';
		std::cout << '\n';
	}

	virtual void push_back(T row)
	{
		data.push_back(row);
	}

	virtual void peek(int size, std::function<std::string(V)> accessor)
	{
		size_t data_size = length();
		size_t peek_size = size > data_size ? data_size : size;

		print_headers();
		for (int i = 0; i < peek_size; ++i)
		{
			for (auto d : data.at(i))
			{
				std::cout << accessor(d) << ',';
			}
			std::cout << '\n';
		}
	}

	std::vector<T> *get_data()
	{
		return &data;
	}

protected:
	std::vector<T> data;
	std::vector<V> partial_data;
};

#endif
