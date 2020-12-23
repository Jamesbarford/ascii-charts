#include <string>
#include <map>

#define PATH "-p"

class CommandLineArgs
{
public:
    CommandLineArgs(int argc, char *argv[])
    {
        for (int i = 1; i < argc; ++i)
        {
            std::string argv_str = std::string(argv[i]);
            if (argv_str.at(0) == prefix)
                command_map[argv_str] = std::string(argv[i + 1]);
        }
    }
    std::string at(std::string);
    void print();

private:
    char prefix = '-';
    std::map<std::string, std::string> command_map;
};
