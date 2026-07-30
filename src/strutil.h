#ifndef STR_UTIL_H
#define STR_UTIL_H

#include <stdbool.h>

char *str_new(char *value);

bool str_append(char **dest, char *value);

bool str_equals(char *str1, char *str2);

int str_hash_code(char *str);

bool str_starts_with(char *str, char *prefix);

bool str_ends_with(char *str, char *suffix);

int str_index_of(char *str, char *substr);

void str_trim(char *str);

bool str_is_empty(char *str);

bool str_is_blank(char *str);

#endif // !STR_UTIL_H