/*
    array utils

    v1.0
*/
#ifndef ARR_UTILS_H
#define ARR_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INVALID_VALUE ((size_t)-1)

/**
* get the max of an int array
* 
* Parameters:
* - arr: int array
* - len: array length
* 
* Returns:
* - max
*/
int arr_imax(int arr[], size_t len);

/**
* get the min of an int array
* 
* Parameters:
* - arr: int array
* - len: array length
* 
* Returns:
* - min
*/
int arr_imin(int arr[], size_t len);

/**
* swap int array elements
* 
* Parameters:
* - arr: int array
* - i1: index
* - i2: other index
*/
void arr_iswap(int arr[], size_t i1, size_t i2);

/**
* check if an int array is in ascending order
* 
* Parameters:
* - arr: int array
* - len: array length
* 
* Returns:
* - yes or no
*/
bool arr_iasc(int arr[], size_t len);

/**
* sort an int array
* 
* Parameters:
* - arr: int array
* - len: array length
*/
void arr_isort(int arr[], size_t len);

/**
* print an int array
* 
* Parameters:
* - arr: int array
* - len: array length
*/
void arr_iprint(int arr[], size_t len);

/**
* get the index of the element with binary search
* 
* Parameters:
* - arr: int array
* - el: element
* - len: array length
* 
* Returns:
* - index
*/
size_t arr_ibsearch(int arr[], int el, size_t len);

/**
* reverse an int array
* 
* Parameters:
* - arr: int array
* - len: array length
*/
void arr_ireverse(int arr[], size_t len);

/**
* copy elements from source to destination
* 
* Parameters:
* - dest: destination
* - src: source
* - num: number of elements
*/
void arr_icopy(int dest[], int src[], size_t num);

#endif // !ARR_UTILS_H