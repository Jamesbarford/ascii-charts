#include <iomanip>

bool is_number(const std::string &s)
{
    auto predicate = [](unsigned char c) -> bool {
        return !std::isdigit(c);
    };

    return !s.empty() && std::find_if(s.begin(), s.end(), predicate) == s.end();
}