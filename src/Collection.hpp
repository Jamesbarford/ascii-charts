#ifndef COLLECTION_CLASS
#define COLLECTION_CLASS

#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <map>

template <typename T>
class Collection
{
public:
    int length()
    {
        return data.size();
    }

    int width()
    {
        return headers.size();
    }

    void collect(std::string raw, int column_idx)
    {
        T d = converter(raw, column_idx);
        if (column_idx + 1 == width())
        {
            partial_data.push_back(d);
            data.push_back(partial_data);
            partial_data.clear();
        }
        else
            partial_data.push_back(d);
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

    std::string converter(std::string raw, int column_idx)
    {
        return raw;
    }

    virtual void push_back(std::vector<T> row)
    {
        data.push_back(row);
    }

    virtual void peek(int size, std::function<std::string(T)> accessor)
    {
        for (int i = 0; i < size; ++i)
        {
            for (auto d : data.at(i))
            {
                std::cout << accessor(d) << ',';
            }
            std::cout << '\n';
        }
    }

    virtual void peek(int size)
    {
        peek(size, [](T d) -> std::string {
            return d;
        });
    }

    std::map<int, std::string> headers;

protected:
    std::vector<std::vector<T>> data;
    std::vector<T> partial_data;
};

#endif
