#include "SearchAndSort.h"
#include "../../DataStructures/header/mergeSort.h"
#include <algorithm>
#include <iostream>
#include <cctype>
#include <sstream>
#include <functional>

// Wrapper structure for sorting Book pointers by title
struct BookTitleWrapper
{
    Book *book;
    BookTitleWrapper() : book(nullptr) {}
    BookTitleWrapper(Book *b) : book(b) {}
    bool operator<(const BookTitleWrapper &other) const
    {
        return book->getTitle() < other.book->getTitle();
    }
};

// Wrapper structure for sorting Book pointers by year
struct BookYearWrapper
{
    Book *book;
    BookYearWrapper() : book(nullptr) {}
    BookYearWrapper(Book *b) : book(b) {}
    bool operator<(const BookYearWrapper &other) const
    {
        return book->getYear() < other.book->getYear();
    }
};

// Wrapper structure for sorting Book pointers by author
struct BookAuthorWrapper
{
    Book *book;
    BookAuthorWrapper() : book(nullptr) {}
    BookAuthorWrapper(Book *b) : book(b) {}
    bool operator<(const BookAuthorWrapper &other) const
    {
        return book->getAuthor() < other.book->getAuthor();
    }
};

// Constructor
SearchAndSort::SearchAndSort(BookManager *manager) : bookManager(manager)
{
    autoCompleteTrie = new Trie();
}

// Destructor
SearchAndSort::~SearchAndSort()
{
    delete autoCompleteTrie;
}

// Auto-completion function using Trie
vector<string> SearchAndSort::autoComplete(const string &prefix)
{
    if (prefix.empty())
    {
        return vector<string>();
    }

    return autoCompleteTrie->getAutoComplete(prefix);
}

// Add book title to Trie for auto-completion
void SearchAndSort::addToAutoComplete(const string &title)
{
    if (!title.empty())
    {
        autoCompleteTrie->insert(title);
    }
}

// Load all book titles from BookManager into Trie
void SearchAndSort::loadAllBooksToTrie()
{
    // Get all books from BookManager
    auto allBooks = bookManager->getAllBooks();

    // Add each book title to the Trie
    for (const auto &entry : allBooks)
    {
        const Book &book = entry.second;
        addToAutoComplete(book.getTitle());
    }

    cout << "Loaded " << allBooks.size() << " book titles into auto-complete." << endl;
}

// Search function - search books by partial title match
vector<Book *> SearchAndSort::searchBooksByTitle(const string &searchTerm)
{
    vector<Book *> results;

    if (searchTerm.empty())
    {
        return results;
    }

    // Get all books from BookManager
    auto allBooks = bookManager->getAllBooks();

    // Convert search term to lowercase for case-insensitive search
    string lowerSearchTerm = searchTerm;
    transform(lowerSearchTerm.begin(), lowerSearchTerm.end(), lowerSearchTerm.begin(), ::tolower);

    // Search through all books for title matches
    for (auto &entry : allBooks)
    {
        Book &book = const_cast<Book &>(entry.second);
        string lowerTitle = book.getTitle();
        transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);

        // Check if the search term is found in the title
        if (lowerTitle.find(lowerSearchTerm) != string::npos)
        {
            results.push_back(&book);
        }
    }

    return results;
}

// Sort books by title using merge sort
void SearchAndSort::sortBooksByTitle(Book *books[], int size)
{
    if (size <= 1)
        return;

    // Create wrapper array
    BookTitleWrapper *wrappers = new BookTitleWrapper[size];
    for (int i = 0; i < size; i++)
        wrappers[i] = BookTitleWrapper(books[i]);

    // Use the imported mergeSort function
    mergeSort(wrappers, 0, size - 1);

    // Copy sorted pointers back
    for (int i = 0; i < size; i++)
        books[i] = wrappers[i].book;

    delete[] wrappers;
    cout << "Books sorted by title successfully using merge sort." << endl;
}

// Sort books by year using merge sort
void SearchAndSort::sortBooksByYear(Book *books[], int size)
{
    if (size <= 1)
        return;

    // Create wrapper array
    BookYearWrapper *wrappers = new BookYearWrapper[size];
    for (int i = 0; i < size; i++)
        wrappers[i] = BookYearWrapper(books[i]);

    // Use the imported mergeSort function
    mergeSort(wrappers, 0, size - 1);

    // Copy sorted pointers back
    for (int i = 0; i < size; i++)
        books[i] = wrappers[i].book;

    delete[] wrappers;
    cout << "Books sorted by year successfully using merge sort." << endl;
}

// Sort books by author using merge sort
void SearchAndSort::sortBooksByAuthor(Book *books[], int size)
{
    if (size <= 1)
        return;

    // Create wrapper array
    BookAuthorWrapper *wrappers = new BookAuthorWrapper[size];
    for (int i = 0; i < size; i++)
        wrappers[i] = BookAuthorWrapper(books[i]);

    // Use the imported mergeSort function
    mergeSort(wrappers, 0, size - 1);

    // Copy sorted pointers back
    for (int i = 0; i < size; i++)
        books[i] = wrappers[i].book;

    delete[] wrappers;
    cout << "Books sorted by author successfully using merge sort." << endl;
}

// Helper comparator functions
bool SearchAndSort::compareByTitle(const Book &a, const Book &b)
{
    return a.getTitle() < b.getTitle();
}

bool SearchAndSort::compareByYear(const Book &a, const Book &b)
{
    return a.getYear() < b.getYear();
}

bool SearchAndSort::compareByAuthor(const Book &a, const Book &b)
{
    return a.getAuthor() < b.getAuthor();
}
