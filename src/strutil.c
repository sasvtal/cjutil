#include "strutil.h"

#include <stdlib.h>
#include <string.h>

char *str_new(char *value)
{
    size_t len = strlen(value);

    char *str = malloc(len + 1);
    if (str == NULL) return NULL;

    memcpy(str, value, len + 1);

    return str;
}

bool str_append(char **dest, char *value)
{
    size_t d_len = strlen(*dest);
    size_t v_len = strlen(value);

    char *str = realloc(*dest, d_len + v_len + 1);
    if (str == NULL) return false;

    memcpy(str + d_len, value, v_len + 1);
    *dest = str;

    return true;
}

bool str_equals(char *str1, char *str2)
{
    return strcmp(str1, str2) == 0;
}

int str_hash_code(char *str)
{
    int code = 1;

    for (char *p = str; *p != '\0'; ++p)
        code = (code << 5) - code + *p;

    return code;
}

bool str_starts_with(char *str, char *prefix)
{
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

bool str_ends_with(char *str, char *suffix)
{
    size_t len = strlen(str);
    size_t s_len = strlen(suffix);

    return len >= s_len && str_equals(str + (len - s_len), suffix);
}

int str_index_of(char *str, char *substr)
{
    char *p = strstr(str, substr);

    return p == NULL ? -1 : p - str;
}

void str_trim(char *str)
{
    int left = 0;
    int right = (int)strlen(str) - 1;

    for (; left <= right && str[left] <= ' '; ++left);
    for (; right > left && str[right] <= ' '; --right);

    int count = 0;
    if (left <= right)
        memmove(
            str,
            str + left,
            (count = right - left + 1)
        );

    str[count] = '\0';
}

bool str_is_empty(char *str)
{
    return str[0] == '\0';
}

bool str_is_blank(char *str)
{
    for (char *p = str; *p != '\0'; ++p)
        if (*p > ' ') return false;

    return true;
}