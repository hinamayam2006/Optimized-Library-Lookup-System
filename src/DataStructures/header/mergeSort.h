#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <string>
using namespace std;

template <typename T>
void mergeSort(T arr[], int left, int right);

template <typename T>
void merge(T arr[], int left, int mid, int right);

#endif
