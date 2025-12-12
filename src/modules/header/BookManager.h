#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include "../entities/header/book.h"               // Adjust path if necessary
#include "../../DataStructures/header/HashTable.h" // Adjust path if necessary
#include <string>
#include <vector>
#include <fstream> // Required for file handling
#include <sstream> // Required for string splitting
#include <iostream>

class BookManager
{
private:
    // Assuming the HashTable stores <int key, Book value>
    HashTable<int, Book> *bookTable;
    std::string csvFilePath; // Store the CSV file path for auto-saving

public:
    // Constructor
    BookManager();

    // Destructor
    ~BookManager();

    // add, delete, search, update and loading books functions:
    void addBook(int id, std::string title, std::string author, int year, std::string publisher = "Unknown");
    bool deleteBook(int id);
    Book *searchBook(int id);                               // Returns pointer to book if found, nullptr if not
    std::vector<Book> searchBookByTitle(std::string title); // Search by title (case-insensitive partial match)
    bool updateBook(int id, std::string newTitle, std::string newAuthor, int newYear);
    void loadBooksFromCSV(std::string filename);
    void saveBooksToCSV(std::string filename);

    // Get all books from the hash table
    std::vector<std::pair<int, Book>> getAllBooks();
};

#endif