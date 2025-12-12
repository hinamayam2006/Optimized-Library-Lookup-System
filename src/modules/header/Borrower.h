#ifndef BORROWER_H
#define BORROWER_H

#include "../../DataStructures/header/HashTable.h"
#include "../../DataStructures/header/linkedList.h"
#include "../../entities/header/BorrowRecord.h"
#include <string>
#include <fstream>
#include <iostream>

class BookManager;

class Borrower
{
private:
    // Map userName -> list of "bookTitle|date" strings
    HashTable<std::string, LinkedList<std::string>> *userToBooks;

    // Map bookTitle -> list of "userName|date" strings
    HashTable<std::string, LinkedList<std::string>> *bookToUsers;

    // Global chronological history stored as lines "userId,bookId,date,action"
    LinkedList<std::string> *history;

    // CSV file path for persistence
    std::string csvFilePath;

    // Pointer to BookManager for validation
    BookManager *bookManager;

    // Helper to append a single CSV record
    void appendRecordToCSV(const std::string &userName, const std::string &bookTitle, const std::string &date, const std::string &action);

public:
    Borrower(const std::string &borrowCsvPath = "D:/HP/Projects/DSAE/Optimized-Library-Lookup-System/data/borrow_records.csv");
    ~Borrower();

    // Borrow a book (adds to maps, history and persists to CSV)
    bool borrowBook(const std::string &userName, const std::string &bookTitle, const std::string &date);

    // Return a book (removes from active maps, records return in history & CSV)
    bool returnBook(const std::string &userName, const std::string &bookTitle, const std::string &date);

    // Load all records from CSV (rebuilds in-memory maps and history)
    void loadBorrowRecordsFromCSV(const std::string &filename);

    // Get pointer to a user's active borrow list (may be nullptr)
    LinkedList<std::string> *getUserActiveBorrows(const std::string &userName);

    // Get pointer to a book's active borrowers list (may be nullptr)
    LinkedList<std::string> *getBookActiveBorrowers(const std::string &bookTitle);

    // Append a custom history entry (not persisted automatically)
    void addHistoryEntry(const std::string &entry);

    // Access the full history list
    LinkedList<std::string> *getHistory() { return history; }

    // Set BookManager for validation
    void setBookManager(BookManager *manager) { bookManager = manager; }
};

#endif
