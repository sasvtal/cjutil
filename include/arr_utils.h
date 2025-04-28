/*
    array utils
*/
#ifndef ARR_UTILS_H
#define ARR_UTILS_H

/*
    create an int array
*/
int *arr_i_new(int len);

/*
    fill the array with the an element
*/
void arr_i_fill(int arr[], int len, int el);

/*
    print the array
*/
void arr_i_print(int arr[], int len);

/*
    copy elements from source to array
*/
void arr_i_copy(int arr[], int src[], int num);

/*
    find the element using binary search
*/
int arr_i_binary_search(int arr[], int len, int el);

/*
    sort the array
*/
void arr_i_sort(int arr[], int len);

#endif // !ARR_UTILS_H