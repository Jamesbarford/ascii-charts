#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <chrono>

class Timer
{
public:
	Timer(std::string label)
	{
		_label = label;
	}
	void start();
	void end();

private:
	std::string _label;
	std::chrono::steady_clock::time_point time_start;
};

#endif
