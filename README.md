# DSA Enabled Library Lookup System

A modern library management system with Qt GUI, demonstrating the practical use cases and benefits of various data structures. Implements hash tables, trie, linked list, merge sort, and more with a user-friendly graphical interface.

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

### 🎨 **Modern Qt GUI**

- Clean, intuitive tabbed interface
- Responsive layout with 1400x900 window size
- Real-time status updates with color-coded messages
- Auto-populating date fields for borrowing operations
- Compact list displays with optimized spacing

### 1. **Book Management**

- Add books with ID, title, author, year, and publisher
- Search books by ID (O(1) average)
- Update book information
- Delete books
- Load/save books from/to CSV files
- Display all books in organized list view

### 2. **Auto-Completion (Trie)**

- Fast book title suggestions as you type
- Case-insensitive search
- Prefix-based filtering
- Interactive suggestion selection

### 3. **Efficient Searching & Sorting**

- Search books by partial title match
- Case-insensitive search
- Returns all matching books
- Sort by title alphabetically
- Sort by publication year
- Sort by author name
- O(n log n) time complexity

### 4. **Borrowing System**

- Borrow and return books
- Track active borrows by user
- Track borrowers by book title
- Complete borrowing history
- Automatic date population
- Validation for book existence

### 5. **Data Persistence**

- Automatic CSV storage
- Load books and borrow records on startup
- Real-time synchronization between memory and files

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
│       ├── LibraryGUI.h        # Qt GUI header
│       └── LibraryGUI.cpp      # Qt GUI implementation
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

- **C++17 or higher**
- **CMake 3.16+**
- **Qt 6.10.1** (MinGW 64-bit build)
- **MinGW-w64 GCC 13.2.0** or later
- **Windows 10 or later**

### Qt Installation

1. Download Qt 6.10.1 from [qt.io](https://www.qt.io/download)
2. Install MinGW 64-bit version
3. Note your Qt installation path (e.g., `D:/HP/BigThings/6.10.1/mingw_64`)

### Build Steps

```powershell
# Navigate to project directory
cd D:\HP\Projects\DSAE\Optimized-Library-Lookup-System

# Create build directory (if not exists)
mkdir build
cd build

# Configure with CMake (update Qt path as needed)
cmake -G "MinGW Makefiles" ..

# Build the project
mingw32-make

# Run the executable
.\LibrarySystem.exe
```

### First Time Setup

After building for the first time, you may need to deploy Qt DLLs:

```powershell
# From build directory
D:\HP\BigThings\6.10.1\mingw_64\bin\windeployqt.exe LibrarySystem.exe
```

### Quick Rebuild

After making code changes:

```powershell
cd build
mingw32-make
.\LibrarySystem.exe
```

## Usage

### GUI Overview

The application features a tabbed interface with three main sections:

#### 📚 Book Management Tab

- **Input Fields**: Book ID, Title, Author, Year, Publisher
- **Operations**: Add, Update, Delete, Search by ID
- **File Operations**: Load CSV, Save CSV, Display All
- **Display Area**: Shows all books or search results

#### 🔍 Search & Sort Tab

- **Search Input**: Type to search with auto-complete suggestions
- **Search Operation**: Search by partial title match
- **Sort Options**: Sort by Title, Year, or Author
- **Results Display**: Shows filtered or sorted results
- **Reload Trie**: Refresh auto-complete database

#### 👥 Borrowing Tab

- **Input Fields**: User Name, Book Title, Date (auto-populated)
- **Operations**: Borrow Book, Return Book
- **View Options**:
  - View User Borrows (by user name)
  - View Book Borrowers (by book title)
  - View Complete History
- **Load Records**: Reload borrowing data from CSV

### Quick Start Guide

1. **Launch Application**: Run `LibrarySystem.exe`
2. **Load Books**: Click "Load CSV" in Book Management tab
3. **Add Books**: Fill in book details and click "Add Book"
4. **Search**: Use Search & Sort tab for finding books
5. **Borrow**: Go to Borrowing tab, enter details, click "Borrow Book"

### Keyboard Shortcuts

- Type in search field for instant auto-complete suggestions
- Click suggestions to auto-fill search term
- Status messages appear at bottom of each tab

### Data Files

Ensure these CSV files exist in the `data/` directory:

- `book.csv` - Book database
- `borrow_records.csv` - Borrowing records
- `user.csv` - User information (optional)

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

✅ **Modern Qt GUI** - Clean, responsive interface with tabbed layout
✅ **Real-time Data Persistence** - Automatic CSV updates
✅ **Fast Lookup** - O(1) average search by ID using hash tables
✅ **Auto-completion** - Efficient prefix-based suggestions with Trie
✅ **Efficient Sorting** - Guaranteed O(n log n) performance with merge sort
✅ **Borrowing System** - Complete book lending and tracking functionality
✅ **Type-Safe** - Template-based generic data structures
✅ **Memory Efficient** - Chaining-based hash table
✅ **User-Friendly** - Color-coded status messages and auto-populating fields
✅ **No Console Window** - Pure GUI application (Windows subsystem)

## Implementation Notes

- All string operations are case-insensitive where applicable
- CSV file is overwritten completely on save (all books are rewritten)
- Wrapper structures (BookTitleWrapper, BookYearWrapper, BookAuthorWrapper) enable merge sort compatibility
- Hash table uses modulo operation for hashing integers
- Automatic file syncing occurs after every add/update/delete operation
- Qt signals and slots used for event handling
- QListWidget items use compact spacing (2px vertical padding) for efficient display
- Date fields auto-populate with current date in YYYY-MM-DD format
- Window size: 1400x900 pixels (adjustable)
- Compiled as Windows GUI application (no console window)

## Technology Stack

- **Language**: C++17
- **GUI Framework**: Qt 6.10.1
- **Build System**: CMake 3.16+
- **Compiler**: MinGW-w64 GCC 13.2.0
- **Platform**: Windows 10+

## Migration History

This project was originally built with FLTK GUI and has been successfully migrated to Qt 6 for:

- Modern look and feel
- Better cross-platform support
- Enhanced widget capabilities
- Improved layout management
- Native Windows integration
