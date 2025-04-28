#include "str_utils.h"

#include <stdlib.h>
#include <string.h>

char *str_new(char *value)
{
    int len = strlen(value) + 1;

    char *s = (char *)malloc(len);
    if (s == NULL) return NULL;

    strcpy(s, value);

    return s;
}

bool str_append(char **str, char *value)
{
    int len = strlen(*str) + strlen(value) + 1;

    char *s = (char *)realloc(*str, len);
    if (s == NULL) return false;

    strcat(s, value);
    *str = s;

    return true;
}

bool str_starts_with(char *str, char *prefix)
{
    return str == strstr(str, prefix);
}

bool str_ends_with(char *str, char *suffix)
{
    return str_starts_with(str + (strlen(str) - strlen(suffix)), suffix);
}

char *str_value_of_int(int value)
{
    if (value == 0) return str_new("0");

    bool neg = false;
    if (value < 0)
    {
        neg = true;
        value *= -1;
    }

    int count = 0;
    for (int n = value; n != 0; n /= 10) count++;

    count = neg ? count + 2 : count + 1;

    char *s = (char *)malloc(count);
    if (s == NULL) return NULL;

    s[count - 1] = '\0';
    if (neg) s[0] = '-';

    int index = count - 2;
    for (int n = value; n != 0; n /= 10)
        s[index--] = (char)((n % 10) + 48);

    return s;
}

int str_index_of_sub(char *str, char *substr, int start_index)
{
    int len = strlen(str);

    if (start_index >= len) return -1;

    char *s = strstr(str + start_index, substr);
    if (s == NULL) return -1;

    return s - str;
}

char *str_trim(char *str)
{
    int len = strlen(str);
    int left = 0;
    int right = len - 1;

    for (; left < len && str[left] <= ' '; left++);
    for (; right >= 0 && str[right] <= ' '; right--);

    int count = right - left + 1;

    char *s = (char *)malloc(count + 1);
    if (s == NULL) return NULL;

    strncpy(s, str + left, count);

    return s;
}

bool str_is_empty(char *str)
{
    return strlen(str) == 0;
}

bool str_is_blank(char *str)
{
    int len = strlen(str);

    for (int i = 0; i < len; i++)
        if (str[i] > ' ') return false;

    return true;
}

int str_hash_code(char *str)
{
    int len = strlen(str);
    int code = 0;

    for (int i = 0; i < len;)
    {
        int n = (int)str[i++];

        n = (n << i) ^ n;
        code += n;
    }

    return code;
}