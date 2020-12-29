#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <vector>

#define NULL_STRING_POSITION std::string::npos
#define NULL_TERMINATING_STRING "\0"
#define NULL_TERMINATING_CHAR '\0'

bool string_contains(std::string *s, std::string seq);
bool string_contains(std::string *s, char seq);
bool some_match(std::string *s, char **seq);
bool is_null_position(size_t pos);
bool str_cmp(char *str1, char *str2);
size_t find_first_position(std::string *s, char **seq);
size_t seq_position(std::string *s, std::string seq);
size_t seq_position(std::string *s, char seq);
std::string remove_seq(std::string *s, char seq);
// remove ascii characters that do not match the predicate
std::string get_ascii_between(std::string *s, std::function<bool(char)> predicate);
std::string get_ascii_between(std::string *s, int lower, int upper);
std::string get_ascii_between(std::string *s, int lower, int upper, int skip);
std::string get_ascii_between_case_insensitive(std::string *s, int lower, int upper);
std::string remove_at(std::string *s, size_t pos, size_t char_size);
std::vector<std::string> find_tokens(std::string *s, char **seq);

class StringSanitizer
{
public:
	StringSanitizer(std::string str)
	{
		_str = str;
	}
	StringSanitizer *remove_char_at(size_t pos, size_t char_size);
	StringSanitizer *filter(std::function<bool(char)> predicate);
	std::string value();
	std::vector<std::string> get_tokens(char **);
	void print();

private:
	std::string _str;
};

#endif
