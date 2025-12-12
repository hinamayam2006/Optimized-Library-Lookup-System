#include "../../DataStructures/header/HashTable.h"
#include "../../DataStructures/header/linkedList.h"
#include "../header/Borrower.h"
#include <sstream>
#include <ctime>

Borrower::Borrower(const std::string &borrowCsvPath)
{
    userToBooks = new HashTable<int, LinkedList<std::string>>();
    bookToUsers = new HashTable<int, LinkedList<std::string>>();
    history = new LinkedList<std::string>();
    csvFilePath = borrowCsvPath;

    // Try to load any existing records
    loadBorrowRecordsFromCSV(csvFilePath);
}

Borrower::~Borrower()
{
    // We don't attempt to write a full rewrite here; records are appended on every operation.
    delete userToBooks;
    delete bookToUsers;
    delete history;
}

void Borrower::appendRecordToCSV(int userId, int bookId, const std::string &date, const std::string &action)
{
    std::ofstream out(csvFilePath, std::ios::app);
    if (!out.is_open())
    {
        std::cerr << "Borrower: could not open " << csvFilePath << " for appending." << std::endl;
        return;
    }

    out << userId << "," << bookId << "," << date << "," << action << "\n";
    out.close();
}

bool Borrower::borrowBook(int userId, int bookId, const std::string &date)
{
    // Create formatted strings for the different lists
    std::string userEntry = std::to_string(bookId) + "|" + date;   // stored in user->books
    std::string bookEntry = std::to_string(userId) + "|" + date;   // stored in book->users
    std::string hist = std::to_string(userId) + "," + std::to_string(bookId) + "," + date + ",borrow";

    // Update userToBooks
    LinkedList<std::string> *uList = userToBooks->search(userId);
    if (uList)
    {
        uList->insertAtEnd(userEntry);
    }
    else
    {
        LinkedList<std::string> newList;
        newList.insertAtEnd(userEntry);
        userToBooks->insert(userId, newList);
    }

    // Update bookToUsers
    LinkedList<std::string> *bList = bookToUsers->search(bookId);
    if (bList)
    {
        bList->insertAtEnd(bookEntry);
    }
    else
    {
        LinkedList<std::string> newList;
        newList.insertAtEnd(bookEntry);
        bookToUsers->insert(bookId, newList);
    }

    // Add to in-memory history
    history->insertAtEnd(hist);

    // Persist by appending to CSV
    appendRecordToCSV(userId, bookId, date, "borrow");

    std::cout << "Borrow recorded: user " << userId << " borrowed book " << bookId << " on " << date << std::endl;
    return true;
}

bool Borrower::returnBook(int userId, int bookId, const std::string &date)
{
    // Construct formatted entries to remove
    std::string userEntry = std::to_string(bookId) + "|" + date; // exact-date removal attempt

    // Because the return date may differ from borrow date, we'll try to remove any entry with bookId for the user
    LinkedList<std::string> *uList = userToBooks->search(userId);
    bool removedFromUser = false;
    if (uList)
    {
        // We need to search the list for an entry that starts with bookId
        // Since LinkedList only provides search/remove by equality, we'll attempt to remove by building possible entries.
        // Strategy: iterate common date formats by looking through CSV-backed history to find matching borrow for this user/book.
        // Fallback: try to remove any exact match with provided date; if not found, do a best-effort scan of history for most recent borrow.

        // Try exact date removal first
        removedFromUser = uList->remove(userEntry);

        if (!removedFromUser)
        {
            // Scan history (we appended all borrows/returns) backwards would be ideal, but LinkedList has no iterator.
            // We'll do a best-effort: attempt to remove any entry with prefix "bookId|" by trying to reconstruct possible entries from CSV file.
            std::ifstream in(csvFilePath);
            if (in.is_open())
            {
                std::string line;
                std::string foundDate;
                while (std::getline(in, line))
                {
                    std::stringstream ss(line);
                    std::string uStr, bStr, dStr, act;
                    if (!std::getline(ss, uStr, ',')) continue;
                    if (!std::getline(ss, bStr, ',')) continue;
                    if (!std::getline(ss, dStr, ',')) continue;
                    if (!std::getline(ss, act, ',')) continue;

                    if (std::stoi(uStr) == userId && std::stoi(bStr) == bookId && act == "borrow")
                    {
                        foundDate = dStr;
                        // Try to remove that specific borrow entry
                        std::string candidate = std::to_string(bookId) + "|" + foundDate;
                        if (uList->remove(candidate))
                        {
                            removedFromUser = true;
                            break;
                        }
                    }
                }
                in.close();
            }
        }
    }

    // Remove from bookToUsers similarly
    LinkedList<std::string> *bList = bookToUsers->search(bookId);
    bool removedFromBook = false;
    if (bList)
    {
        // try exact date remove
        std::string exact = std::to_string(userId) + "|" + date;
        removedFromBook = bList->remove(exact);

        if (!removedFromBook)
        {
            // attempt to find borrow date from CSV
            std::ifstream in(csvFilePath);
            if (in.is_open())
            {
                std::string line;
                std::string foundDate;
                while (std::getline(in, line))
                {
                    std::stringstream ss(line);
                    std::string uStr, bStr, dStr, act;
                    if (!std::getline(ss, uStr, ',')) continue;
                    if (!std::getline(ss, bStr, ',')) continue;
                    if (!std::getline(ss, dStr, ',')) continue;
                    if (!std::getline(ss, act, ',')) continue;

                    if (std::stoi(uStr) == userId && std::stoi(bStr) == bookId && act == "borrow")
                    {
                        foundDate = dStr;
                        std::string candidate = std::to_string(userId) + "|" + foundDate;
                        if (bList->remove(candidate))
                        {
                            removedFromBook = true;
                            break;
                        }
                    }
                }
                in.close();
            }
        }
    }

    // Record return in history and CSV regardless of whether removal succeeded (best-effort)
    std::string hist = std::to_string(userId) + "," + std::to_string(bookId) + "," + date + ",return";
    history->insertAtEnd(hist);
    appendRecordToCSV(userId, bookId, date, "return");

    if (removedFromUser || removedFromBook)
    {
        std::cout << "Return processed: user " << userId << " returned book " << bookId << " on " << date << std::endl;
        return true;
    }

    std::cout << "Return recorded, but no active borrow entry was found for user " << userId << " and book " << bookId << std::endl;
    return false;
}

void Borrower::loadBorrowRecordsFromCSV(const std::string &filename)
{
    std::ifstream in(filename);
    if (!in.is_open())
    {
        // No file yet; that's fine
        return;
    }

    std::string line;
    while (std::getline(in, line))
    {
        if (line.size() == 0) continue;
        std::stringstream ss(line);
        std::string uStr, bStr, dStr, act;

        if (!std::getline(ss, uStr, ',')) continue;
        if (!std::getline(ss, bStr, ',')) continue;
        if (!std::getline(ss, dStr, ',')) continue;
        if (!std::getline(ss, act, ',')) continue;

        int userId = 0;
        int bookId = 0;
        try
        {
            userId = std::stoi(uStr);
            bookId = std::stoi(bStr);
        }
        catch (...) { continue; }

        // Always add to global history
        std::string hist = uStr + "," + bStr + "," + dStr + "," + act;
        history->insertAtEnd(hist);

        if (act == "borrow")
        {
            // Add to userToBooks
            LinkedList<std::string> *uList = userToBooks->search(userId);
            std::string userEntry = std::to_string(bookId) + "|" + dStr;
            if (uList)
            {
                uList->insertAtEnd(userEntry);
            }
            else
            {
                LinkedList<std::string> newList;
                newList.insertAtEnd(userEntry);
                userToBooks->insert(userId, newList);
            }

            // Add to bookToUsers
            LinkedList<std::string> *bList = bookToUsers->search(bookId);
            std::string bookEntry = std::to_string(userId) + "|" + dStr;
            if (bList)
            {
                bList->insertAtEnd(bookEntry);
            }
            else
            {
                LinkedList<std::string> newList;
                newList.insertAtEnd(bookEntry);
                bookToUsers->insert(bookId, newList);
            }
        }
        else if (act == "return")
        {
            // On return, remove the corresponding borrow entries if present
            LinkedList<std::string> *uList = userToBooks->search(userId);
            if (uList)
            {
                // remove any entry matching bookId|date
                std::string candidate = std::to_string(bookId) + "|" + dStr;
                uList->remove(candidate);
            }

            LinkedList<std::string> *bList = bookToUsers->search(bookId);
            if (bList)
            {
                std::string candidate = std::to_string(userId) + "|" + dStr;
                bList->remove(candidate);
            }
        }
    }

    in.close();
}

LinkedList<std::string> *Borrower::getUserActiveBorrows(int userId)
{
    return userToBooks->search(userId);
}

LinkedList<std::string> *Borrower::getBookActiveBorrowers(int bookId)
{
    return bookToUsers->search(bookId);
}

void Borrower::addHistoryEntry(const std::string &entry)
{
    history->insertAtEnd(entry);
}
