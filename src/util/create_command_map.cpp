#include <iostream>

#include "CommandMap.hpp"

CommandMap create_command_map(int argc, char **argv)
{
    CommandMap command_map;

    for (int i = 1; i < argc; ++i)
    {
        std::string argv_str = std::string(argv[i]);
        if (argv_str.at(0) == PREFIX)
        {
            std::vector<std::string> args;
            for (int j = i + 1; j < argc; ++j)
            {
                std::string next_arg = std::string(argv[j]);
                if (next_arg.at(0) == PREFIX || next_arg == "")
                    break;
                args.push_back(next_arg);
            }
            command_map[argv_str] = args;
        }
    }

    return command_map;
}
