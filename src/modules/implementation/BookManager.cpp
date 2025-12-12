#include "BookManager.h"   //includes header file
#include <algorithm>
#include <cctype>

// constructor
BookManager::BookManager()
{
    // Initializing hash table for storage
    bookTable = new HashTable<int, Book>();                                            
    // CSV file path
    csvFilePath = "D:/HP/Projects/DSAE/Optimized-Library-Lookup-System/data/book.csv"; 
}

// destructor
BookManager::~BookManager()
{
    // Clean up allocated memory to avoid memory leaks
    delete bookTable;
}

//-----------1.ADD BOOK FUNCTION-----------
// Adds a new book to the hash table and auto-saves to CSV
void BookManager::addBook(int id, std::string title, std::string author, int year, std::string publisher)
{
    // Check if book's ID is unique before adding
    if (bookTable->search(id) != nullptr)
    {
        std::cout << "Book ID already exists. Skipping add." << std::endl;
        return;
    }

    // Creation of new book object
    Book newBook(id, title, author, year, publisher);

    // Insertion in hash table
    // Key is ID, Value is Book object
    bookTable->insert(id, newBook);

    std::cout << "Book added successfully: " << title << std::endl;

    // Auto-save changes to CSV file
    if (!csvFilePath.empty())
    {
        saveBooksToCSV(csvFilePath);
    }
}

// -----------2-A. SEARCHING BOOK BY ID-----------
//Hash table lookup by ID
Book *BookManager::searchBook(int id)
{
    // Use Hash Table's search function
    return bookTable->search(id);    // O(1) average time complexity
}

// -----------2-B. SEARCHING BOOK BY TITLE-----------
//linear search through all books for title match
std::vector<Book> BookManager::searchBookByTitle(std::string title)
{
    std::vector<Book> results;

    // Convert searched book's title to lowercase for case-insensitivity
    std::string lowerSearchTerm = title;
    std::transform(lowerSearchTerm.begin(), lowerSearchTerm.end(), lowerSearchTerm.begin(), ::tolower);

    // Get all books from hash table to iterate through
    auto allBooks = getAllBooks();

    // Search through all books for matching title
    for (const auto &entry : allBooks)
    {
        const Book &book = entry.second;
        // Convert current book title to lowercase
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

//-----------3. DELETE FUNCTION-----------
// Deletes a book by ID and updates CSV
bool BookManager::deleteBook(int id)
{
    // Check if book exists
    if (bookTable->search(id) == nullptr)
    {
        std::cout << "Book not found!" << std::endl;
        return false;
    }
    // Remove book from hash table
    bookTable->remove(id);
    std::cout << "Book deleted successfully." << std::endl;

    // Update CSV file after deletion
    if (!csvFilePath.empty())
    {
        saveBooksToCSV(csvFilePath);
    }

    return true;
}

//---------- 4. UPDATE FUNCTION-----------
// Updates book details and auto-saves to CSV
bool BookManager::updateBook(int id, std::string newTitle, std::string newAuthor, int newYear)
{
    Book *book = bookTable->search(id);
    // Check if book exists
    if (book != nullptr)
    {
        // Update the fields of the book
        book->setTitle(newTitle);
        book->setAuthor(newAuthor);
        book->setYear(newYear);
        std::cout << "Book updated successfully." << std::endl;

        // Save changes to CSV file
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

//---------- 5. LOAD BOOKS FROM CSV FUNCTION-----------
// Loads books from a CSV file into the hash table
void BookManager::loadBooksFromCSV(std::string filename)
{
    csvFilePath = filename;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    // Skip header line
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

            // CSV format: ID,Title,Author,Year,Publisher

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

            // 5. Get Publisher (Optional)
            if (!std::getline(ss, publisher, ','))
                publisher = "Unknown";

            // Add book to the hash table
            Book newBook(id, title, author, year, publisher);
            bookTable->insert(id, newBook);
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

//---------6. SAVE BOOKS TO CSV FUNCTION-----------
// Saves all books from the hash table to a CSV file
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

    // loop through all books and write each book to CSV
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

//----------7. GET ALL BOOKS FUNCTION-----------
std::vector<std::pair<int, Book>> BookManager::getAllBooks()
{
    return bookTable->getAllEntries();
}