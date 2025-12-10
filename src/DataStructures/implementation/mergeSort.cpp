#include "../header/mergeSort.h"
#include "../../entities/header/book.h"

// Wrapper structures for Book pointer sorting
struct BookTitleWrapper {
    Book* book;
    BookTitleWrapper() : book(nullptr) {}
    BookTitleWrapper(Book* b) : book(b) {}
    bool operator<(const BookTitleWrapper& other) const {
        return book->getTitle() < other.book->getTitle();
    }
};

struct BookYearWrapper {
    Book* book;
    BookYearWrapper() : book(nullptr) {}
    BookYearWrapper(Book* b) : book(b) {}
    bool operator<(const BookYearWrapper& other) const {
        return book->getYear() < other.book->getYear();
    }
};

struct BookAuthorWrapper {
    Book* book;
    BookAuthorWrapper() : book(nullptr) {}
    BookAuthorWrapper(Book* b) : book(b) {}
    bool operator<(const BookAuthorWrapper& other) const {
        return book->getAuthor() < other.book->getAuthor();
    }
};

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
template void mergeSort<BookTitleWrapper>(BookTitleWrapper[], int, int);
template void mergeSort<BookYearWrapper>(BookYearWrapper[], int, int);
template void mergeSort<BookAuthorWrapper>(BookAuthorWrapper[], int, int);
