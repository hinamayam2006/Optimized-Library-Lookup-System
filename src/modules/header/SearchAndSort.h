#ifndef SEARCH_AND_SORT_H
#define SEARCH_AND_SORT_H

#include "../header/BookManager.h"
#include "../../DataStructures/header/trie.h"
#include "../../DataStructures/header/mergeSort.h"
#include <vector>
#include <string>

using namespace std;

class SearchAndSort
{
private:
    BookManager *bookManager;
    Trie *autoCompleteTrie;

public:
    // Constructor and Destructor
    SearchAndSort(BookManager *manager);
    ~SearchAndSort();

    // Auto-completion function using Trie
    vector<string> autoComplete(const string &prefix);

    // Add book title to Trie for auto-completion
    void addToAutoComplete(const string &title);
    
    // Load all book titles from BookManager into Trie
    void loadAllBooksToTrie();

    // Search function - search books by title
    vector<Book *> searchBooksByTitle(const string &title);

    // Sorting functions
    void sortBooksByTitle(Book *books[], int size);
    void sortBooksByYear(Book *books[], int size);
    void sortBooksByAuthor(Book *books[], int size);

private:
    // Helper comparator for merge sort
    static bool compareByTitle(const Book &a, const Book &b);
    static bool compareByYear(const Book &a, const Book &b);
    static bool compareByAuthor(const Book &a, const Book &b);
};

#endif
