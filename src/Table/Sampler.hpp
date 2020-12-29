#ifndef SAMPLER_CLASS
#define SAMPLER_CLASS

#include <vector>
#include <string>
#include <map>

#include "../Collection.hpp"
#include "TypeMapping.hpp"

class Sampler : public Collection<std::vector<std::string>, std::string>
{
public:
	bool complete = false;
	unsigned int sample_size;
	Sampler(unsigned int size)
	{
		sample_size = size;
	};
	virtual std::string converter(std::string raw, int column_idx)
	{
		return raw;
	}

	bool should_collect(int row_idx, int column_idx);
	std::vector<std::vector<std::string>> *get_sample_data();
	TypeMapping to_type_mapping();
};

#endif
