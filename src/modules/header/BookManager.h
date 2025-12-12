#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

//dependencies
#include "../entities/header/book.h"               // include Book entity
#include "../../DataStructures/header/HashTable.h" // include to Hash Table
#include <string>
#include <vector>
#include <fstream> // Required for file handling
#include <sstream> // Required for string splitting
#include <iostream>

// Controls the operations related to books
class BookManager
{
private:
    //Stores books using their ID as the unique key
    HashTable<int, Book> *bookTable;
    std::string csvFilePath; // Store the CSV file path for auto-saving

public:
    // Constructor
    BookManager();

    // Destructor
    ~BookManager();

    // Adds a new book to the library and triggers an auto-save
    void addBook(int id, std::string title, std::string author, int year, std::string publisher = "Unknown");

    // Removes a book by its unique ID. Returns true if successful
    bool deleteBook(int id);

    // Updates details (Title, Author, Year) of an existing book. Returns true if successful.
    bool updateBook(int id, std::string newTitle, std::string newAuthor, int newYear);

    // Reads the CSV file
    void loadBooksFromCSV(std::string filename);

    // Overwrites the CSV file with current data to ensure changes are saved
    void saveBooksToCSV(std::string filename);

    // O(1) complexity: Finds a book by its ID, returns nullptr if not found
    Book *searchBook(int id);  
    
    // O(N) complexity: Finds all books containing searched title, returns pointer to book if found, nullptr if not
    std::vector<Book> searchBookByTitle(std::string title); // Search by title (case-insensitive partial match)
    
    // Converts Hash Table data into a Vector 
    std::vector<std::pair<int, Book>> getAllBooks();
};

#endif