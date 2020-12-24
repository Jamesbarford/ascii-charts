#ifndef COMMAND_MAP_H
#define COMMAND_MAP_H

#include <string>
#include <map>
#include <vector>

#define PATH "-p"
#define PREFIX '-'

typedef std::map<std::string, std::vector<std::string>> CommandMap;
CommandMap create_command_map(int argc, char **argv);

#endif
