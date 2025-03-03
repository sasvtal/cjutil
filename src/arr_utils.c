#include "arr_utils.h"

/**
* recursion
* sort an int array with quick sort
*/
static void iqsort(int arr[], size_t start, size_t end);



int arr_imax(int arr[], size_t len)
{
    int max = arr[0];
    for (size_t i = 1; i < len; i++)
    {
        int el = arr[i];
        if (el > max) max = el;
    }

    return max;
}

int arr_imin(int arr[], size_t len)
{
    int min = arr[0];
    for (size_t i = 1; i < len; i++)
    {
        int el = arr[i];
        if (el < min) min = el;
    }

    return min;
}

void arr_iswap(int arr[], size_t i1, size_t i2)
{
    int temp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = temp;
}

bool arr_iasc(int arr[], size_t len)
{
    int base = arr[0];
    for (size_t i = 1; i < len; i++)
    {
        int el = arr[i];
        if (el < base) return false;

        base = el;
    }

    return true;
}

void arr_isort(int arr[], size_t len)
{
    iqsort(arr, 0, len - 1);
}

void arr_iprint(int arr[], size_t len)
{
    size_t last = len - 1;

    printf("[");
    for (size_t i = 0; i < len; i++)
    {
        printf("%d", arr[i]);
        if (i < last) printf(", ");
    }
    printf("]\n");
}

size_t arr_ibsearch(int arr[], int el, size_t len)
{
    size_t left = 0;
    size_t right = len - 1;

    while (left <= right && right != INVALID_VALUE)
    {
        size_t mid = (left + right) >> 1;
        int base = arr[mid];

        if (el < base) right = mid - 1;
        else if (el > base) left = mid + 1;
        else return mid;
    }

    return INVALID_VALUE;
}

void arr_ireverse(int arr[], size_t len)
{
    size_t last = len - 1;
    size_t end = len >> 1;

    for (size_t i = 0; i < end; i++)
        arr_iswap(arr, i, last - i);
}

void arr_icopy(int dest[], int src[], size_t num)
{
    for (size_t i = 0; i < num; i++)
        dest[i] = src[i];
}



static void iqsort(int arr[], size_t start, size_t end)
{
    if (start > end || end == INVALID_VALUE) return;

    size_t left = start;
    size_t right = end;
    int base = arr[start];

    while (true)
    {
        while (left < right && arr[right] >= base) right--;
        while (left < right && arr[left] <= base) left++;

        if (left == right) break;

        arr_iswap(arr, left, right);
    }

    arr_iswap(arr, start, left);

    iqsort(arr, start, right - 1);
    iqsort(arr, left + 1, end);
}