#include <iostream>

#include "CommandLineArgs.hpp"

void CommandLineArgs::print()
{
    for (auto [first, second] : command_map)
        std::cout << first << " :" << second << '\n';
}

std::string CommandLineArgs::at(std::string key)
{
    return command_map.at(key);
}