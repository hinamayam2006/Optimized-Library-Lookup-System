#include "../../DataStructures/header/HashTable.h"
#include "../../DataStructures/header/linkedList.h"
#include "../header/Borrower.h"
#include "../header/BookManager.h"
#include <sstream>
#include <ctime>

Borrower::Borrower(const std::string &borrowCsvPath)
{
    userToBooks = new HashTable<std::string, LinkedList<std::string>>();
    bookToUsers = new HashTable<std::string, LinkedList<std::string>>();
    history = new LinkedList<std::string>();
    csvFilePath = borrowCsvPath;
    bookManager = nullptr;

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

void Borrower::appendRecordToCSV(const std::string &userName, const std::string &bookTitle, const std::string &date, const std::string &action)
{
    std::ofstream out(csvFilePath, std::ios::app);
    if (!out.is_open())
    {
        std::cerr << "Borrower: could not open " << csvFilePath << " for appending." << std::endl;
        return;
    }

    out << userName << "," << bookTitle << "," << date << "," << action << "\n";
    out.close();
}

bool Borrower::borrowBook(const std::string &userName, const std::string &bookTitle, const std::string &date)
{
    // Validate that book exists in BookManager
    if (bookManager)
    {
        auto books = bookManager->searchBookByTitle(bookTitle);
        if (books.empty())
        {
            std::cerr << "Error: Book '" << bookTitle << "' does not exist in the library!" << std::endl;
            return false;
        }
    }

    // Check if book is already borrowed by anyone
    LinkedList<std::string> *bookBorrowers = bookToUsers->search(bookTitle);
    if (bookBorrowers)
    {
        auto borrowers = bookBorrowers->toVector();
        if (!borrowers.empty())
        {
            // Extract the borrower's name from first entry (format: "userName|date")
            std::string firstEntry = borrowers[0];
            size_t pipePos = firstEntry.find('|');
            std::string currentBorrower = (pipePos != std::string::npos) ? firstEntry.substr(0, pipePos) : firstEntry;
            std::cerr << "Error: Book '" << bookTitle << "' is already borrowed by '" << currentBorrower << "'!" << std::endl;
            return false;
        }
    }

    // Check if user already has this book borrowed
    LinkedList<std::string> *userBorrows = userToBooks->search(userName);
    if (userBorrows)
    {
        // Check if any entry starts with the bookTitle
        for (const auto &entry : userBorrows->toVector())
        {
            // Entry format: "bookTitle|date"
            size_t pipePos = entry.find('|');
            if (pipePos != std::string::npos)
            {
                std::string existingBook = entry.substr(0, pipePos);
                if (existingBook == bookTitle)
                {
                    std::cerr << "Error: User '" << userName << "' has already borrowed '" << bookTitle << "'!" << std::endl;
                    return false;
                }
            }
        }
    }

    // Create formatted strings for the different lists
    std::string userEntry = bookTitle + "|" + date; // stored in user->books
    std::string bookEntry = userName + "|" + date;  // stored in book->users
    std::string hist = userName + "," + bookTitle + "," + date + ",borrow";

    // Update userToBooks
    LinkedList<std::string> *uList = userToBooks->search(userName);
    if (uList)
    {
        uList->insertAtEnd(userEntry);
    }
    else
    {
        LinkedList<std::string> newList;
        newList.insertAtEnd(userEntry);
        userToBooks->insert(userName, newList);
    }

    // Update bookToUsers
    LinkedList<std::string> *bList = bookToUsers->search(bookTitle);
    if (bList)
    {
        bList->insertAtEnd(bookEntry);
    }
    else
    {
        LinkedList<std::string> newList;
        newList.insertAtEnd(bookEntry);
        bookToUsers->insert(bookTitle, newList);
    }

    // Add to in-memory history
    history->insertAtEnd(hist);

    // Persist by appending to CSV
    appendRecordToCSV(userName, bookTitle, date, "borrow");

    std::cout << "Borrow recorded: user '" << userName << "' borrowed book '" << bookTitle << "' on " << date << std::endl;
    return true;
}

bool Borrower::returnBook(const std::string &userName, const std::string &bookTitle, const std::string &date)
{
    // Construct formatted entries to remove
    std::string userEntry = bookTitle + "|" + date; // exact-date removal attempt

    // Because the return date may differ from borrow date, we'll try to remove any entry with bookId for the user
    LinkedList<std::string> *uList = userToBooks->search(userName);
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
                    if (!std::getline(ss, uStr, ','))
                        continue;
                    if (!std::getline(ss, bStr, ','))
                        continue;
                    if (!std::getline(ss, dStr, ','))
                        continue;
                    if (!std::getline(ss, act, ','))
                        continue;

                    if (uStr == userName && bStr == bookTitle && act == "borrow")
                    {
                        foundDate = dStr;
                        // Try to remove that specific borrow entry
                        std::string candidate = bookTitle + "|" + foundDate;
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
    LinkedList<std::string> *bList = bookToUsers->search(bookTitle);
    bool removedFromBook = false;
    if (bList)
    {
        // try exact date remove
        std::string exact = userName + "|" + date;
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
                    if (!std::getline(ss, uStr, ','))
                        continue;
                    if (!std::getline(ss, bStr, ','))
                        continue;
                    if (!std::getline(ss, dStr, ','))
                        continue;
                    if (!std::getline(ss, act, ','))
                        continue;

                    if (uStr == userName && bStr == bookTitle && act == "borrow")
                    {
                        foundDate = dStr;
                        std::string candidate = userName + "|" + foundDate;
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
    std::string hist = userName + "," + bookTitle + "," + date + ",return";
    history->insertAtEnd(hist);
    appendRecordToCSV(userName, bookTitle, date, "return");

    if (removedFromUser || removedFromBook)
    {
        std::cout << "Return processed: user '" << userName << "' returned book '" << bookTitle << "' on " << date << std::endl;
        return true;
    }

    std::cout << "Return recorded, but no active borrow entry was found for user '" << userName << "' and book '" << bookTitle << "'" << std::endl;
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
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string userName, bookTitle, date, action;
        if (!std::getline(ss, userName, ','))
            continue;
        if (!std::getline(ss, bookTitle, ','))
            continue;
        if (!std::getline(ss, date, ','))
            continue;
        if (!std::getline(ss, action, ','))
            continue;

        // Append to history
        history->insertAtEnd(userName + "," + bookTitle + "," + date + "," + action);

        if (action == "borrow")
        {
            // user -> books
            if (auto uList = userToBooks->search(userName))
            {
                uList->insertAtEnd(bookTitle + "|" + date);
            }
            else
            {
                LinkedList<std::string> newList;
                newList.insertAtEnd(bookTitle + "|" + date);
                userToBooks->insert(userName, newList);
            }

            // book -> users
            if (auto bList = bookToUsers->search(bookTitle))
            {
                bList->insertAtEnd(userName + "|" + date);
            }
            else
            {
                LinkedList<std::string> newList;
                newList.insertAtEnd(userName + "|" + date);
                bookToUsers->insert(bookTitle, newList);
            }
        }
        else if (action == "return")
        {
            if (auto uList = userToBooks->search(userName))
            {
                uList->remove(bookTitle + "|" + date);
            }
            if (auto bList = bookToUsers->search(bookTitle))
            {
                bList->remove(userName + "|" + date);
            }
        }
    }

    in.close();
}

LinkedList<std::string> *Borrower::getUserActiveBorrows(const std::string &userName)
{
    return userToBooks->search(userName);
}

LinkedList<std::string> *Borrower::getBookActiveBorrowers(const std::string &bookTitle)
{
    return bookToUsers->search(bookTitle);
}

void Borrower::addHistoryEntry(const std::string &entry)
{
    history->insertAtEnd(entry);
}
