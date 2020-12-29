#include <functional>
#include <iostream>
#include <string.h>
#include "string_util.hpp"

void for_each_char(char **char_seq, std::function<bool(char *)> iteratee)
{
    int i = -1;
    char *str;

    while (!str_cmp((str = char_seq[++i]), (char *)NULL_TERMINATING_STRING))
        if (iteratee(str) == true)
            break;
}

bool str_cmp(char *str1, char *str2)
{
    return strcmp(str1, str2) == 0;
}

bool string_contains(std::string *s, std::string seq)
{
    return !is_null_position(seq_position(s, seq));
}

bool string_contains(std::string *s, char seq)
{
    return !is_null_position(seq_position(s, seq));
}

bool is_null_position(size_t pos)
{
    return pos == NULL_STRING_POSITION;
}

bool some_match(std::string *s, char **seq)
{
    bool contains = false;

    for_each_char(seq, [&s, &contains](char *str) -> bool {
        contains = string_contains(s, str);
        return contains;
    });

    return contains;
}

size_t find_first_position(std::string *s, char **seq)
{
    size_t pos;

    for_each_char(seq, [&s, &pos](char *str) -> bool {
        pos = seq_position(s, str);
        return !is_null_position(pos);
    });

    return !is_null_position(pos) ? pos : NULL_STRING_POSITION;
}

size_t seq_position(std::string *s, char seq)
{
    return seq_position(s, std::to_string(seq));
}

size_t seq_position(std::string *s, std::string seq)
{
    if (s->empty())
        return NULL_STRING_POSITION;

    return s->find(seq);
}

std::string remove_seq(std::string *s, char seq)
{
    std::string new_string = "";
    char cur_char;

    for (size_t i = 0; i < s->size(); ++i)
    {
        cur_char = s->at(i);
        if (!(cur_char == seq))
            new_string.push_back(cur_char);
    }

    return new_string;
}

std::string remove_at(std::string *s, size_t pos, size_t char_size)
{
    if (is_null_position(pos))
        return *s;
    if (pos == 0)
        return s->substr(char_size, s->size());

    return s->substr(0, pos) + s->substr(pos + char_size, s->size() - char_size);
}

std::string get_ascii_between(std::string *s, std::function<bool(char)> predicate)
{
    std::string new_str;

    for (auto c : *s)
        if (predicate(c))
            new_str += c;

    return new_str;
}

/* case sensetive */
std::string get_ascii_between(std::string *s, int lower, int upper, int skip)
{
    return get_ascii_between(s, [&](char c) -> bool {
        return (c == skip) || (c >= lower && c <= upper);
    });
}

/* case sensetive */
std::string get_ascii_between(std::string *s, int lower, int upper)
{
    return get_ascii_between(s, [&](char c) -> bool {
        return (c >= lower && c <= upper);
    });
}

std::string get_ascii_between_case_insensitive(std::string *s, int lower, int upper)
{
    return get_ascii_between(s, [&](char c) -> bool {
        char lower_case = tolower(c);
        return (lower_case >= lower && lower_case <= upper);
    });
}

std::vector<std::string> find_tokens(std::string *s, char **seq)
{
    size_t pos;
    std::vector<std::string> tokens;
    for_each_char(seq, [&s, &pos, &tokens](char *str) -> bool {
        pos = seq_position(s, str);
        if (!is_null_position(pos))
            tokens.push_back(str);

        return false;
    });
    return tokens;
}

StringSanitizer *StringSanitizer::filter(std::function<bool(char)> predicate)
{
    this->_str = get_ascii_between(&_str, predicate);
    return this;
}

StringSanitizer *StringSanitizer::remove_char_at(size_t pos, size_t char_size)
{
    if (is_null_position(pos))
        return this;
    this->_str = remove_at(&this->_str, pos, char_size);
    return this;
}

std::string StringSanitizer::value()
{
    return this->_str;
}

void StringSanitizer::print()
{
    std::cout << " str :: " << _str << "\n";
}

std::vector<std::string> StringSanitizer::get_tokens(char **seq)
{
    return find_tokens(&this->_str, seq);
}
