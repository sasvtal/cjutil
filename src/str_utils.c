#include "str_utils.h"

char *str_copy(char *str)
{
    size_t len = strlen(str) + 1;

    char *s = (char *)malloc(len);
    if (s == NULL) return NULL;

    strcpy(s, str);

    return s;
}

bool str_append(char **src, char *str)
{
    size_t len = strlen(*src) + strlen(str) + 1;

    char *s = (char *)realloc(*src, len);
    if (s == NULL) return false;

    strcat(s, str);
    *src = s;

    return true;
}

char **str_split(char *str, char *delim, size_t num)
{
    size_t count = str_count(str, delim);
    if (count == INVALID_VALUE) return NULL;

    count++;

    if (num == 0 || num > count) num = count;

    char **arr = (char **)malloc((num + 1) * sizeof(char *));
    if (arr == NULL) return NULL;

    arr[num] = NULL;
    size_t len = strlen(delim);

    char *s = str;
    for (size_t i = 0; ; i++)
    {
        arr[i] = s;
        if (i == num - 1) break;

        size_t index = str_index(s, delim, 0);
        s[index] = '\0';
        index += len;
        s += index;
    }

    return arr;
}

bool str_start(char *str, char *pre)
{
    return str == strstr(str, pre);
}

bool str_end(char *str, char *suf)
{
    return str_start(str + (strlen(str) - strlen(suf)), suf);
}

char *str_int(int val)
{
    if (val == 0) return str_copy("0");

    bool neg = false;
    if (val < 0)
    {
        neg = true;
        val *= -1;
    }

    size_t count = 0;
    for (int n = val; n != 0; n /= 10) count++;

    count = neg ? count + 2 : count + 1;

    char *s = (char *)malloc(count);
    if (s == NULL) return NULL;

    s[count - 1] = '\0';
    if (neg) s[0] = '-';

    size_t index = count - 2;
    for (int n = val; n != 0; n /= 10)
        s[index--] = (char)((n % 10) + 48);

    return s;
}

size_t str_index(char *str, char *sub, size_t index)
{
    size_t len = strlen(str);

    if (index >= len)
    {
        if (len > 0) return INVALID_VALUE;

        index = 0;
    }

    char *s = strstr(str + index, sub);
    if (s == NULL) return INVALID_VALUE;

    return s - str;
}

size_t str_count(char *str, char *sub)
{
    size_t len = strlen(sub);
    if (len == 0) return INVALID_VALUE;

    size_t count = 0;
    for (
        char *s = str;
        (s = strstr(s, sub)) != NULL;
        s += len
    ) count++;

    return count;
}

void str_trim(char *str)
{
    size_t len = strlen(str);
    size_t start = 0;
    size_t end = len - 1;

    for (; start < len && str[start] < 33; start++);

    for (; end >= 0 && str[end] < 33; end--);

    size_t count = end - start + 1;
    memmove(str, str + start, count);
    str[count] = '\0';
}

bool str_empty(char *str)
{
    return strlen(str) == 0;
}

bool str_blank(char *str)
{
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++)
        if (str[i] > 32) return false;

    return true;
}