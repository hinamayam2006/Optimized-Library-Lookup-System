#include "BookManager.h"
#include <algorithm>
#include <cctype>

BookManager::BookManager()
{
    bookTable = new HashTable<int, Book>();                                            // Initialize the hash table
    csvFilePath = "D:/HP/Projects/DSAE/Optimized-Library-Lookup-System/data/book.csv"; // Use consistent path with GUI
}

BookManager::~BookManager()
{
    delete bookTable;
}

// 1. ADD FUNCTION
void BookManager::addBook(int id, std::string title, std::string author, int year, std::string publisher)
{
    // Disallow duplicate IDs to keep primary key uniqueness
    if (bookTable->search(id) != nullptr)
    {
        std::cout << "Book ID already exists. Skipping add." << std::endl;
        return;
    }

    // Create a new book object
    Book newBook(id, title, author, year, publisher);

    // Insert into hash table
    // The Key is the ID, the Value is the Book object
    bookTable->insert(id, newBook);

    std::cout << "Book added successfully: " << title << std::endl;

    // Auto-save to CSV file if path is set
    if (!csvFilePath.empty())
    {
        saveBooksToCSV(csvFilePath);
    }
}

// 2. SEARCH FUNCTION BY ID
Book *BookManager::searchBook(int id)
{
    // Use the Hash Table's search function
    // This is O(1) on average - very efficient!
    return bookTable->search(id);
}

// 2B. SEARCH FUNCTION BY TITLE
std::vector<Book> BookManager::searchBookByTitle(std::string title)
{
    std::vector<Book> results;

    // Convert search term to lowercase for case-insensitive search
    std::string lowerSearchTerm = title;
    std::transform(lowerSearchTerm.begin(), lowerSearchTerm.end(), lowerSearchTerm.begin(), ::tolower);

    // Get all books from hash table
    auto allBooks = getAllBooks();

    // Search through all books for title matches
    for (const auto &entry : allBooks)
    {
        const Book &book = entry.second;
        std::string lowerTitle = book.getTitle();
        std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);

        // Check if the search term is found in the title
        if (lowerTitle.find(lowerSearchTerm) != std::string::npos)
        {
            results.push_back(book);
        }
    }

    return results;
}

// 3. DELETE FUNCTION
bool BookManager::deleteBook(int id)
{
    if (bookTable->search(id) == nullptr)
    {
        std::cout << "Book not found!" << std::endl;
        return false;
    }

    bookTable->remove(id);
    std::cout << "Book deleted successfully." << std::endl;

    // Auto-save to CSV file if path is set
    if (!csvFilePath.empty())
    {
        saveBooksToCSV(csvFilePath);
    }

    return true;
}

// 4. UPDATE FUNCTION
bool BookManager::updateBook(int id, std::string newTitle, std::string newAuthor, int newYear)
{
    Book *book = bookTable->search(id);

    if (book != nullptr)
    {
        // Update the fields
        book->setTitle(newTitle);
        book->setAuthor(newAuthor);
        book->setYear(newYear);
        std::cout << "Book updated successfully." << std::endl;

        // Auto-save to CSV file if path is set
        if (!csvFilePath.empty())
        {
            saveBooksToCSV(csvFilePath);
        }

        return true;
    }
    else
    {
        std::cout << "Cannot update: Book ID not found." << std::endl;
        return false;
    }
}

// 5. LOAD BOOKS FROM CSV FUNCTION
void BookManager::loadBooksFromCSV(std::string filename)
{
    csvFilePath = filename; // Store the filename for auto-saving
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    // Skip the header line if your CSV has one (e.g., "ID,Title,Author...")
    // std::getline(file, line);

    while (std::getline(file, line))
    {
        try
        {
            std::stringstream ss(line);
            std::string segment;

            // Variables to hold parsed data
            int id;
            std::string title, author, yearStr, publisher;
            int year;

            // Assumes CSV format: ID,Title,Author,Year,Publisher

            // 1. Get ID
            if (!std::getline(ss, segment, ','))
                continue;
            id = std::stoi(segment);

            // 2. Get Title
            if (!std::getline(ss, title, ','))
                continue;

            // 3. Get Author
            if (!std::getline(ss, author, ','))
                continue;

            // 4. Get Year
            if (!std::getline(ss, yearStr, ','))
                continue;
            year = std::stoi(yearStr);

            // 5. Get Publisher (Optional, handles if missing)
            if (!std::getline(ss, publisher, ','))
                publisher = "Unknown";

            // Reuse your existing add function to store it in the Hash Table!
            this->addBook(id, title, author, year, publisher);
        }
        catch (const std::exception &e)
        {
            // Skip malformed rows
            std::cerr << "Warning: Skipping malformed CSV row: " << line << std::endl;
            continue;
        }
    }

    file.close();
    std::cout << "Data loaded successfully from " << filename << std::endl;
}

// SAVE BOOKS TO CSV FUNCTION
void BookManager::saveBooksToCSV(std::string filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write header
    file << "ID,Title,Author,Year,Publisher" << std::endl;

    // Get all books from the hash table
    auto entries = bookTable->getAllEntries();

    // Write each book to CSV
    for (const auto &entry : entries)
    {
        const Book &book = entry.second;
        file << book.getId() << ","
             << book.getTitle() << ","
             << book.getAuthor() << ","
             << book.getYear() << ","
             << book.getPublisher() << std::endl;
    }

    file.close();
    std::cout << "Data saved successfully to " << filename << std::endl;
}

// GET ALL BOOKS FUNCTION
std::vector<std::pair<int, Book>> BookManager::getAllBooks()
{
    return bookTable->getAllEntries();
}