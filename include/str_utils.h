/*
    string utils
*/
#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <stdbool.h>

/*
    create a string
*/
char *str_new(char *value);

/*
    append the value to the string
*/
bool str_append(char **str, char *value);

/*
    check if the string starts with the prefix
*/
bool str_starts_with(char *str, char *prefix);

/*
    check if the string ends with the suffix
*/
bool str_ends_with(char *str, char *suffix);

/*
    convert an int value to a string
*/
char *str_value_of_int(int value);

/*
    find the index of the first occurrence of a substring
*/
int str_index_of_sub(char *str, char *substr, int start_index);

/*
    trim space from the beginning and end of a string
*/
char *str_trim(char *str);

/*
    check if the string is empty
*/
bool str_is_empty(char *str);

/*
    check if the string is blank
*/
bool str_is_blank(char *str);

/*
    calculate the hash code for the string
*/
int str_hash_code(char *str);

#endif // !STR_UTILS_H