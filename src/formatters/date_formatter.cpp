#include <chrono>
#include <sstream>
#include <iomanip>

#include "date_formatter.hpp"

std::string to_date_string(long long ms, std::string pattern)
{
	auto date_ms = std::chrono::milliseconds(ms);
	auto time_point = std::chrono::time_point<std::chrono::system_clock>(date_ms);
	auto in_time_t = std::chrono::system_clock::to_time_t(time_point);
	auto local_time = std::localtime(&in_time_t);

	std::stringstream ss;
	ss << std::put_time(local_time, pattern.c_str());
	return ss.str();
}
