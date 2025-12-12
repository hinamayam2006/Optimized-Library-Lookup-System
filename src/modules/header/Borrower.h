#ifndef BORROWER_H
#define BORROWER_H

#include "../../DataStructures/header/HashTable.h"
#include "../../DataStructures/header/linkedList.h"
#include "../../entities/header/BorrowRecord.h"
#include <string>
#include <fstream>
#include <iostream>

class Borrower
{
private:
    // Map userId -> list of "bookId|date" strings
    HashTable<int, LinkedList<std::string>> *userToBooks;

    // Map bookId -> list of "userId|date" strings
    HashTable<int, LinkedList<std::string>> *bookToUsers;

    // Global chronological history stored as lines "userId,bookId,date,action"
    LinkedList<std::string> *history;

    // CSV file path for persistence
    std::string csvFilePath;

    // Helper to append a single CSV record
    void appendRecordToCSV(int userId, int bookId, const std::string &date, const std::string &action);

public:
    Borrower(const std::string &borrowCsvPath = "data/borrow_records.csv");
    ~Borrower();

    // Borrow a book (adds to maps, history and persists to CSV)
    bool borrowBook(int userId, int bookId, const std::string &date);

    // Return a book (removes from active maps, records return in history & CSV)
    bool returnBook(int userId, int bookId, const std::string &date);

    // Load all records from CSV (rebuilds in-memory maps and history)
    void loadBorrowRecordsFromCSV(const std::string &filename);

    // Get pointer to a user's active borrow list (may be nullptr)
    LinkedList<std::string> *getUserActiveBorrows(int userId);

    // Get pointer to a book's active borrowers list (may be nullptr)
    LinkedList<std::string> *getBookActiveBorrowers(int bookId);

    // Append a custom history entry (not persisted automatically)
    void addHistoryEntry(const std::string &entry);
};

#endif
