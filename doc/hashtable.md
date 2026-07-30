# hashtable

A hashtable

## Working Principle

A new Hashtable instance can be created using `hst_new()`.  
The instance is allocated on the heap using `malloc()` and a pointer to it is returned.  
The parameter `hc` is a function pointer that receives a `void *` and returns an `int`. It is used to calculate the hash code of each key.  
The parameter `eq` is a function pointer that receives two `void *` parameters and returns a `bool`. It is used to determine whether two keys are equal.  
By providing custom `hc` and `eq` functions, the Hashtable can store different types of keys and values.

When inserting a key-value pair using `hst_put()`, the Hashtable first calculates the hash code of the key through `hc`.  
Then, it uses `eq` to check whether the key already exists.  
If the key exists, the old value associated with the key is replaced by the new value, and the old value is returned.  
If the key does not exist, a new `HashEntry` instance is created. The key and value are stored in the entry, and the entry is added to the Hashtable.  
The underlying storage uses a bucket array with separate chaining to store `HashEntry` instances.  
Before inserting a new entry, the Hashtable checks whether the current number of entries has reached the resize threshold.  
If the threshold is reached, the Hashtable is resized before inserting the new entry.  
When a new key-value pair is inserted, `hst_put()` returns `NULL`.  
Note that `NULL` can also be a valid stored value.

## Notes

### Load Factor: 0.75
When:  
`number of entries > bucket count * 0.75`  
the Hashtable will be resized.

### Resize Strategy
The initial bucket count is 11.  
Each resize increases the bucket count using:  
`new capacity = old capacity * 2 + 1`

### Index Calculation
`index = (hash code & INT_MAX) % bucket count`  
Negative hash codes are converted into positive values before calculating the bucket index.

### Memory Management
When the Hashtable is no longer needed, call `hst_free()` to release the resources occupied by the instance.  
This operation will not release individual keys and values.  
The Hashtable only manages its own memory:
- Hashtable instance
- HashEntry instances

The lifetime of keys and values is managed by the caller.  
If keys and values are inserted using dynamically allocated memory directly:  
`hst_put(tab, malloc(...), malloc(...));`  
or if the caller does not keep references to each key and value,  
the user should release them manually before calling `hst_free()`.  
For example:
```c
void myfree(void *k, void *v)
{
    free(k);
    free(v);
}

hst_for_each(tab, myfree);
```

### Iteration
Use `hst_iter_first()` and `hst_iter_next()` to iterate through the Hashtable.  
Make sure to call `hst_iter_first()` before every iteration to ensure that the starting position is correctly initialized.  
Avoid structural modifications such as `hst_put()` and `hst_remove()` during iteration to ensure iteration correctness.

### Thread Safety
The Hashtable is not thread-safe.

## Usage Example
```c
#include "hashtable.h"

int hc(void *k)
{
    return *(int *)k;
}

bool eq(void *k1, void *k2)
{
    return *(int *)k1 == *(int *)k2;
}

int main(void)
{
    Hashtable *tab = hst_new(hc, eq);

    int a = 1;
    int b = 2;
    int c = 3;

    hst_put(tab, &a, &b);
    hst_put(tab, &b, &c);
    hst_put(tab, &c, &a);

    for (
        HashEntry *e = hst_iter_first(tab);
        e != NULL;
        e = hst_iter_next(tab)
    )
    printf(
        "%d=%d\n",
        *(int *)hse_get_key(e),
        *(int *)hse_get_value(e)
    );

    hst_free(&tab);

    return 0;
}
```