# vector

A dynamic array

## Working Principle

A new Vector instance can be created using `vtr_new()`.  
The instance is allocated on the heap using `malloc()` and a pointer to it is returned.

When adding an element using `vtr_add()`,  
the Vector first checks whether the current number of stored elements has reached the resize threshold.  
If the threshold is reached, the Vector is resized before adding the new element.  
The function returns `true` when the element is successfully added.  
Duplicate elements are allowed.

The functions `vtr_get()`, `vtr_set()`, and `vtr_remove()` are index-based operations.  
Please pay attention to the valid index range when using these functions.  
The index parameter uses an unsigned type, so the function cannot receive negative indices internally.  
Passing a negative value through implicit conversion will result in a very large positive value,  
which is treated as an out-of-range index.  
When the index is out of range, all three functions return `NULL`.  
When the index is valid, these functions return the element associated with the specified index.  
Note that `NULL` can also be a valid stored element.

## Notes

### Index Range
Make sure that the index is always within: `[0, size - 1]`

### Resize Strategy
The underlying array is not allocated when the Vector is created.  
The first call to `vtr_add()` triggers the initial allocation.  
An array with a capacity of 10 is created.  
After that, whenever the resize condition is reached, the capacity is increased by:  
`new capacity = old capacity + old capacity / 2`

### Memory Management
When the Vector is no longer needed, call `vtr_free()` to release the resources occupied by the instance.  
This operation will not release individual elements.  
The Vector only manages its own memory.  
If elements are inserted using dynamically allocated memory directly:  
`vtr_add(vec, malloc(...));`  
or if the caller does not keep references to each element,  
the user should release them manually before calling `vtr_free()`.  
For example:
```c
vtr_for_each(vec, free);
```
If the elements have a complex structure, provide a custom release function.

### Iteration
The Vector provides index-based access and can be traversed directly using a `for` loop.  
Avoid structural modifications such as `vtr_add()` and `vtr_remove()` during iteration to ensure iteration correctness.

### Thread Safety
The Vector is not thread-safe.

## Usage Example
```c
#include "vector.h"

int main(void)
{
    Vector *vec = vtr_new();

    int a = 1;
    int b = 2;
    int c = 3;

    vtr_add(vec, &a);
    vtr_add(vec, &b);
    vtr_add(vec, &c);

    for (size_t i = 0, size = vtr_size(vec); i < size; ++i)
        printf("%d\n", *(int *)vtr_get(vec, i));

    vtr_free(&vec);

    return 0;
}
```