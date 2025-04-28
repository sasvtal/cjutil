#include "arr_utils.h"

#include <stdio.h>
#include <stdlib.h>

/*
    recursion
    int quick sort
*/
static void i_quick_sort(int arr[], int start, int end);

/*
    int swap
*/
static void i_swap(int arr[], int i, int j);



int *arr_i_new(int len)
{
    int *arr = (int *)malloc(len * sizeof(int));
    if (arr == NULL) return NULL;

    arr_i_fill(arr, len, 0);

    return arr;
}

void arr_i_fill(int arr[], int len, int el)
{
    for (int i = 0; i < len; i++)
        arr[i] = el;
}

void arr_i_print(int arr[], int len)
{
    int last = len - 1;

    printf("[");
    for (int i = 0; i < len; i++)
    {
        printf("%d", arr[i]);
        if (i < last) printf(", ");
    }
    printf("]\n");
}

void arr_i_copy(int arr[], int src[], int num)
{
    for (int i = 0; i < num; i++)
        arr[i] = src[i];
}

int arr_i_binary_search(int arr[], int len, int el)
{
    int left = 0;
    int right = len - 1;

    while (left <= right)
    {
        int mid = (left + right) >> 1;
        int base = arr[mid];

        if (el < base) right = mid - 1;
        else if (el > base) left = mid + 1;
        else return mid;
    }

    return -1;
}

void arr_i_sort(int arr[], int len)
{
    i_quick_sort(arr, 0, len - 1);
}



static void i_quick_sort(int arr[], int start, int end)
{
    if (start >= end) return;

    int left = start;
    int right = end;
    int base = arr[start];

    while (1)
    {
        while (left < right && arr[right] >= base) right--;
        while (left < right && arr[left] <= base) left++;

        if (left == right) break;

        i_swap(arr, left, right);
    }

    i_swap(arr, start, left);

    i_quick_sort(arr, start, right - 1);
    i_quick_sort(arr, left + 1, end);
}

static void i_swap(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}