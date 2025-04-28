Some small tools in C language, similar to java.util.  
Hope they can be helpful to you.

Please note that these tools are mostly implemented using the malloc().  
Always be mindful of using the free().

Collections:

array  
A dynamic array, similar to Java's ArrayList.  
which allows you to store and access elements.

list  
A doubly linked list, similar to Java's LinkedList.  
You can use it to implement a stack and a queue.

table  
A hash table, similar to Java's HashMap.  
You can use it to store and access key-value pairs.  
When using it, you need to define the hash algorithm and comparison rules for the keys.  
Keys must be unique.

tree  
A binary tree, similar to Java's TreeMap.  
You can use it to store and access key-value pairs, and sort them.  
When using it, you need to define the sorting rules for the keys.  
Keys must be unique.

Each collection provides a release function,  
Please call it to destroy the collection to free the memory when it is no longer in use.  
If you store dynamically allocated elements,  
make sure to use for_each() + free() to release each element before freeing the collection.

Utils:

str_utils  
String utilities, similar to Java's String.  
All returned strings are dynamically allocated.  
Please call the free() to release them when no longer in use.  
If you need to store string-type keys in a table,  
the hash_code() in this tool can help you.

arr_utils  
Array utilities, similar to Java's Arrays.  
This tool is still under development and currently only supports arrays of int type.  
When using binary_search(),  
please note that the array passed in must be sorted in ascending order.
