#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include "Book.h"          // Adjust path if necessary
#include "HashTable.h" // Adjust path if necessary
#include <string>
#include <fstream>  // Required for file handling
#include <sstream>  // Required for string splitting
#include <iostream>

class BookManager {
private:
    // Assuming the HashTable stores <int key, Book value>
    HashTable<int, Book>* bookTable; 

public:
    // Constructor
    BookManager();
    
    // Destructor
    ~BookManager();

    // add, delete, search, update and loading books functions:
    void addBook(int id, std::string title, std::string author, int year, std::string publisher = "Unknown");
    bool deleteBook(int id);
    Book* searchBook(int id); // Returns pointer to book if found, nullptr if not
    bool updateBook(int id, std::string newTitle, std::string newAuthor, int newYear);
    void loadBooksFromCSV(std::string filename);
    // Helper to load/save data might be needed later, but focus on these 4 first.
};

#endif