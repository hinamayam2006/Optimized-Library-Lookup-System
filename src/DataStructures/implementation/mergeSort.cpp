#include "../header/mergeSort.h"

template <typename T>
void merge(T arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    T *L = new T[n1];
    T *R = new T[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
        arr[k++] = (L[i] < R[j]) ? L[i++] : R[j++];

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

template <typename T>
void mergeSort(T arr[], int left, int right)
{
    if (left >= right)
        return;

    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

template void mergeSort<string>(string[], int, int);
template void mergeSort<int>(int[], int, int);
