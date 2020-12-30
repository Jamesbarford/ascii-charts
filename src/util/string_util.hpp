#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <vector>

bool string_contains(std::string *s, std::string seq);
bool string_contains(std::string *s, char seq);
bool some_match(std::string *s, std::vector<std::string>seq);
bool is_null_position(size_t pos);
bool str_cmp(char *str1, char *str2);
bool is_strnum(std::string *s);
size_t find_first_position(std::string *s, std::vector<std::string>seq);
size_t seq_position(std::string *s, std::string seq);
size_t seq_position(std::string *s, char seq);
std::string remove_seq(std::string *s, char seq);
// remove ascii characters that do not match the predicate
std::string get_ascii_between(std::string *s, std::function<bool(char)> predicate);
std::string get_ascii_between(std::string *s, int lower, int upper);
std::string get_ascii_between(std::string *s, int lower, int upper, int skip);
std::string get_ascii_between_case_insensitive(std::string *s, int lower, int upper);
std::string remove_at(std::string *s, size_t pos, size_t char_size);
std::vector<std::string> find_tokens(std::string *s, std::vector<std::string>seq);

#endif
