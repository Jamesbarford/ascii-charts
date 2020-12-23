#include <vector>
#include <string>
#include <map>

#include "TypeMapping.hpp"

typedef std::vector<std::string> SampleData;

class Sampler
{
public:
    void collect(std::string, int);
    void collect_headers(std::string, int);
    void print();
    void print_headers();
    int get_size();
    std::vector<SampleData> *get_parsed_data();
    TypeMapping to_type_mapping();
    std::map<int, std::string> headers;
    std::vector<SampleData> sample;

private:
    SampleData current_sample;
    int column_width = 0;
};