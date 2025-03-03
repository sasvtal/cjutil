/*
    string utils

    v1.0
*/
#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INVALID_VALUE ((size_t)-1)

/**
* copy the string to the heap
* 
* Parameters:
* - str: string
* 
* Returns:
* - string
*/
char *str_copy(char *str);

/**
* append the string to the source
* 
* Parameters:
* - src: source address
* - str: string
* 
* Returns:
* - success or failure
*/
bool str_append(char **src, char *str);

/**
* split the string by the delimiter
* 
* Parameters:
* - str: string
* - delim: delimiter
* - num: max number of results
* 
* Returns:
* - result array
*/
char **str_split(char *str, char *delim, size_t num);

/**
* check if the string starts with the prefix
* 
* Parameters:
* - str: string
* - pre: prefix
* 
* Returns:
* - yes or no
*/
bool str_start(char *str, char *pre);

/**
* check if the string ends with the suffix
* 
* Parameters:
* - str: string
* - suf: suffix
* 
* Returns:
* - yes or no
*/
bool str_end(char *str, char *suf);

/**
* convert an int value to a string
* 
* Parameters:
* - val: int value
* 
* Returns:
* - string
*/
char *str_int(int val);

/**
* find the index of the first occurrence of a substring
* 
* Parameters:
* - str: string
* - sub: substring
* - index: start index of find
* 
* Returns:
* - index
*/
size_t str_index(char *str, char *sub, size_t index);

/**
* count the occurrences of a substring
* 
* Parameters:
* - str: string
* - sub: substring
* 
* Returns:
* - count
*/
size_t str_count(char *str, char *sub);

/**
* trim space from the beginning and end of a string
* 
* Parameters:
* - str: string
*/
void str_trim(char *str);

/**
* check if the string is empty
* 
* Parameters:
* - str: string
* 
* Returns:
* - yes or no
*/
bool str_empty(char *str);

/**
* check if the string is blank
* 
* Parameters:
* - str: string
* 
* Returns:
* - yes or no
*/
bool str_blank(char *str);

#endif // !STR_UTILS_H