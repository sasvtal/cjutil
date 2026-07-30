# strutil

A string util

## API Overview

All functions assume that input parameters are valid and do not perform `NULL` checks.  
Passing `NULL` parameters may result in undefined behavior.

### str_new
Creates a dynamically allocated copy of the given string using `malloc()`  
and returns a pointer to it.  
Note:  
When the returned string is no longer needed,  
call `free()` to release the allocated memory.

### str_append
Appends a string using `realloc()` and returns whether the operation succeeds.  
Note:  
The `dest` parameter must point to a dynamically allocated string created by `malloc()`.  
Otherwise, calling `realloc()` may result in undefined behavior.

### str_equals
Checks whether two strings are equal.

### str_hash_code
Calculates the hash code of a string.

### str_starts_with
Checks whether a string starts with a specified prefix.

### str_ends_with
Checks whether a string ends with a specified suffix.

### str_index_of
Finds the starting index of a substring.  
Returns the index if the substring is found, otherwise returns `-1`.

### str_trim
Removes leading and trailing whitespace characters from a string.  
Note:  
This function modifies the original string directly,  
so string literals cannot be used as parameters.

### str_is_empty
Checks whether a string contains no characters.

### str_is_blank
Checks whether a string contains no characters or only whitespace characters.

## Usage Example
```c
#include "strutil.h"

int main(void)
{
    char *str = str_new(" qwe");
    puts(str);
    // " qwe"

    printf("%d\n", str_append(&str, "a "));
    puts(str);
    // " qwea "

    printf("%d\n", str_starts_with(str, "q"));
    // false

    printf("%d\n", str_ends_with(str, "a "));
    // true

    str_trim(str);
    puts(str);
    // "qwea"

    free(str);

    printf("%d\n", str_is_blank("  \t "));
    // true

    printf("%d\n", str_is_empty("  \t "));
    // false

    return 0;
}
```