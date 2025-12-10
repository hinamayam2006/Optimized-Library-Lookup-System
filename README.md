# Optimized Library Lookup System

Library management system using differetn data structures to show the use case and benifit of them. Uses hashtables, trie, linked list, merge sort etc.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Data Structures](#data-structures)
- [How It Works](#how-it-works)
- [Building the Project](#building-the-project)
- [Usage](#usage)
- [File Format](#file-format)
- [API Documentation](#api-documentation)

## Overview

This project implements an optimized library management system that leverages multiple data structures to provide fast and efficient operations for:

- Adding/searching/updating/deleting books
- Auto-completing book titles
- Sorting books by various criteria
- Persistent data storage

All data is stored in a **Hash Table** for O(1) average-case search and persisted to a CSV file automatically on every change.

## Features

### 1. **Book Management**

- Add books with ID, title, author, year, and publisher
- Search books by ID (O(1) average)
- Update book information
- Delete books
- Load/save books from/to CSV files

### 2. **Auto-Completion (Trie)**

- Fast book title suggestions as you type
- Case-insensitive search
- Prefix-based filtering

### 3. **Efficient Searching**

- Search books by partial title match
- Case-insensitive search
- Returns all matching books

### 4. **High-Performance Sorting (Merge Sort)**

- Sort by title alphabetically
- Sort by publication year
- Sort by author name
- O(n log n) time complexity

### 5. **Data Persistence**

- Automatic CSV storage on every operation
- Load books on startup
- Real-time synchronization between memory and file

## 📁 Project Structure

```
Optimized-Library-Lookup-System/
├── CMakeLists.txt
├── README.md
├── data/
│   ├── book.csv           # Book storage (CSV format)
│   ├── user.csv           # User data
│   └── borrow_records.csv # Borrowing history
├── src/
│   ├── main.cpp           # Entry point
│   ├── DataStructures/
│   │   ├── header/
│   │   │   ├── HashTable.h      # Hash table implementation (template)
│   │   │   ├── linkedList.h     # Linked list
│   │   │   ├── trie.h           # Trie for auto-completion
│   │   │   └── mergeSort.h      # Merge sort algorithm
│   │   └── implementation/
│   │       ├── HashTable.cpp
│   │       ├── linkedList.cpp
│   │       ├── trie.cpp
│   │       └── mergeSort.cpp
│   ├── entities/
│   │   ├── header/
│   │   │   ├── book.h           # Book entity
│   │   │   ├── user.h           # User entity
│   │   │   └── BorrowRecord.h   # Borrow record entity
│   │   └── implementation/
│   │       ├── book.cpp
│   │       ├── user.cpp
│   │       └── BorrowRecord.cpp
│   ├── modules/
│   │   ├── header/
│   │   │   ├── BookManager.h       # Book management module
│   │   │   ├── Borrower.h          # Borrowing module
│   │   │   └── SearchAndSort.h     # Search & sort module
│   │   └── implementation/
│   │       ├── BookManager.cpp
│   │       ├── Borrower.cpp
│   │       └── SearchAndSort.cpp
│   └── UI/
│       ├── consoleUI.h
│       └── consoleUI.cpp
```

## Data Structures

### 1. **Hash Table** (`HashTable.h`)

- **Purpose:** Store books by ID for O(1) average lookup
- **Type:** Template-based with chaining collision resolution
- **Size:** 1000 buckets
- **Key:** Book ID (int)
- **Value:** Book object

```cpp
HashTable<int, Book> bookTable;
bookTable.insert(1, myBook);
Book* found = bookTable.search(1);
```

### 2. **Trie** (`trie.h`)

- **Purpose:** Auto-complete suggestions for book titles
- **Performance:** O(m) where m is the length of the prefix
- **Supports:** Case-insensitive search with prefix matching

```cpp
Trie autoComplete;
autoComplete.insert("The Great Gatsby");
vector<string> suggestions = autoComplete.getAutoComplete("The");
```

### 3. **Merge Sort** (`mergeSort.h`)

- **Purpose:** Efficient sorting of books
- **Time Complexity:** O(n log n) guaranteed
- **Space Complexity:** O(n)
- **Supports:** Generic types via templates

### 4. **Linked List** (`linkedList.h`)

- **Purpose:** Support for other data management needs
- **Operations:** Insert, delete, search, traverse

## How It Works

### Data Flow Diagram

```
CSV File (book.csv)
        ↓
loadBooksFromCSV()
        ↓
    HashTable (Memory)
   ↙        ↙        ↙
BookManager  SearchAndSort  Borrower
   ↙        ↙        ↙
add/update/delete (auto-save)
        ↓
saveBooksToCSV()
        ↓
CSV File (book.csv)
```

### Typical Usage Flow

```cpp
// 1. Create managers
BookManager bookManager;
SearchAndSort searchSort(&bookManager);

// 2. Load books from CSV file
bookManager.loadBooksFromCSV("data/book.csv");

// 3. Load titles into Trie for auto-completion
searchSort.loadAllBooksToTrie();

// 4. Add a new book (auto-saves to CSV)
bookManager.addBook(1, "The Great Gatsby", "F. Scott Fitzgerald", 1925, "Scribner");

// 5. Search for book by ID
Book* book = bookManager.searchBook(1);

// 6. Auto-complete search
vector<string> suggestions = searchSort.autoComplete("The");

// 7. Search by title
vector<Book*> results = searchSort.searchBooksByTitle("gatsby");

// 8. Sort books
Book* allBooks[100];
// ... populate array ...
searchSort.sortBooksByTitle(allBooks, count);
```

## Building the Project

### Prerequisites

- C++11 or higher
- CMake 3.10+
- GCC/Clang compiler

### Build Steps

```bash
# Navigate to project directory
cd Optimized-Library-Lookup-System

# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
cmake --build .

# Run the executable
./OptimizedLibraryLookupSystem
```

## Usage

### Adding a Book

```cpp
bookManager.addBook(1, "1984", "George Orwell", 1949, "Secker & Warburg");
// Automatically saved to book.csv
```

### Searching

```cpp
// Search by ID
Book* book = bookManager.searchBook(1);

// Search by title (partial match)
vector<Book*> results = searchSort.searchBooksByTitle("1984");

// Auto-complete
vector<string> suggestions = searchSort.autoComplete("19");
// Returns: ["1984"]
```

### Sorting

```cpp
Book* books[100];
// ... populate array ...

// Sort by title
searchSort.sortBooksByTitle(books, count);

// Sort by year
searchSort.sortBooksByYear(books, count);

// Sort by author
searchSort.sortBooksByAuthor(books, count);
```

### Updating Books

```cpp
bookManager.updateBook(1, "1984 (Updated Edition)", "George Orwell", 1949);
// Automatically saved to book.csv
```

### Deleting Books

```cpp
bookManager.deleteBook(1);
// Automatically saved to book.csv
```

## File Format

### book.csv

```
ID,Title,Author,Year,Publisher
1,The Great Gatsby,F. Scott Fitzgerald,1925,Scribner
2,1984,George Orwell,1949,Secker & Warburg
3,To Kill a Mockingbird,Harper Lee,1960,J.B. Lippincott
```

The CSV file is automatically maintained and synced with the in-memory Hash Table. Changes are persisted immediately after every operation.

## API Documentation

### BookManager Class

#### Methods

- `BookManager()` - Constructor
- `~BookManager()` - Destructor
- `void addBook(int id, string title, string author, int year, string publisher)` - Add book
- `Book* searchBook(int id)` - Search by ID
- `bool updateBook(int id, string newTitle, string newAuthor, int newYear)` - Update book
- `bool deleteBook(int id)` - Delete book
- `void loadBooksFromCSV(string filename)` - Load from CSV
- `void saveBooksToCSV(string filename)` - Save to CSV
- `vector<pair<int, Book>> getAllBooks()` - Get all books

### SearchAndSort Class

#### Methods

- `SearchAndSort(BookManager* manager)` - Constructor
- `~SearchAndSort()` - Destructor
- `vector<string> autoComplete(string prefix)` - Get suggestions
- `void addToAutoComplete(string title)` - Add title to Trie
- `void loadAllBooksToTrie()` - Load all book titles into Trie
- `vector<Book*> searchBooksByTitle(string title)` - Search by title
- `void sortBooksByTitle(Book* books[], int size)` - Sort by title
- `void sortBooksByYear(Book* books[], int size)` - Sort by year
- `void sortBooksByAuthor(Book* books[], int size)` - Sort by author

## Performance Analysis

| Operation       | Data Structure | Time Complexity | Space Complexity |
| --------------- | -------------- | --------------- | ---------------- |
| Add Book        | Hash Table     | O(1) avg        | O(1)             |
| Search by ID    | Hash Table     | O(1) avg        | O(1)             |
| Update Book     | Hash Table     | O(1) avg        | O(1)             |
| Delete Book     | Hash Table     | O(1) avg        | O(1)             |
| Auto-complete   | Trie           | O(m)            | O(m)             |
| Search by Title | Linear         | O(n)            | O(k)             |
| Sort            | Merge Sort     | O(n log n)      | O(n)             |

## Key Features

✅ **Real-time Data Persistence** - Automatic CSV updates
✅ **Fast Lookup** - O(1) average search by ID
✅ **Auto-completion** - Efficient prefix-based suggestions
✅ **Efficient Sorting** - Guaranteed O(n log n) performance
✅ **Type-Safe** - Template-based generic data structures
✅ **Memory Efficient** - Chaining-based hash table
✅ **Easy Integration** - Modular design with clear APIs

## Implementation Notes

- All string operations are case-insensitive where applicable
- CSV file is overwritten completely on save (all books are rewritten)
- Wrapper structures (BookTitleWrapper, BookYearWrapper, BookAuthorWrapper) enable merge sort compatibility
- Hash table uses modulo operation for hashing integers
- Automatic file syncing occurs after every add/update/delete operation
