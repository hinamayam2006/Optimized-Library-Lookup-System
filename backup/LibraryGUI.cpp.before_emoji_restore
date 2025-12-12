#include "LibraryGUI.h"
#include <FL/Fl_Tabs.H>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>

LibraryGUI::LibraryGUI(int w, int h, const char *title)
    : Fl_Window(w, h, title)
{
    // Initialize managers
    bookManager = new BookManager();
    searchAndSort = new SearchAndSort(bookManager);
    borrower = new Borrower("D:/HP/Projects/DSAE/Optimized-Library-Lookup-System/data/borrow_records.csv");

    // Load existing books from CSV
    bookManager->loadBooksFromCSV("D:/HP/Projects/DSAE/Optimized-Library-Lookup-System/data/book.csv");
    searchAndSort->loadAllBooksToTrie();

    // Link borrower with bookManager for validation
    borrower->setBookManager(bookManager);

    // Create tabbed interface
    Fl_Tabs *tabs = new Fl_Tabs(10, 10, w - 20, h - 20);

    // ============ BOOK MANAGEMENT TAB ============
    bookManagementTab = new Fl_Group(10, 35, w - 20, h - 45, "Book Management");

    // Title labels and inputs
    Fl_Box *idLabel = new Fl_Box(20, 50, 80, 25, "Book Code:");
    bookIdInput = new Fl_Int_Input(110, 50, 100, 25);

    Fl_Box *titleLabel = new Fl_Box(20, 85, 80, 25, "Title:");
    bookTitleInput = new Fl_Input(110, 85, 200, 25);

    Fl_Box *authorLabel = new Fl_Box(20, 120, 80, 25, "Author:");
    bookAuthorInput = new Fl_Input(110, 120, 200, 25);

    Fl_Box *yearLabel = new Fl_Box(20, 155, 80, 25, "Year:");
    bookYearInput = new Fl_Int_Input(110, 155, 100, 25);

    Fl_Box *publisherLabel = new Fl_Box(20, 190, 80, 25, "Publisher:");
    bookPublisherInput = new Fl_Input(110, 190, 200, 25);

    // Buttons for Book Management
    addBookBtn = new Fl_Button(20, 230, 90, 30, "Add Book");
    addBookBtn->callback(addBookCallback, (void *)this);

    updateBookBtn = new Fl_Button(120, 230, 90, 30, "Update");
    updateBookBtn->callback(updateBookCallback, (void *)this);

    deleteBookBtn = new Fl_Button(220, 230, 90, 30, "Delete");
    deleteBookBtn->callback(deleteBookCallback, (void *)this);

    searchBookBtn = new Fl_Button(320, 230, 110, 30, "Search");
    searchBookBtn->callback(searchBookCallback, (void *)this);

    loadBooksBtn = new Fl_Button(20, 270, 90, 30, "Load Books");
    loadBooksBtn->callback(loadBooksCallback, (void *)this);

    saveBooksBtn = new Fl_Button(120, 270, 90, 30, "Save Books");
    saveBooksBtn->callback(saveBooksCallback, (void *)this);

    displayAllBooksBtn = new Fl_Button(220, 270, 90, 30, "Display All");
    displayAllBooksBtn->callback(displayAllBooksCallback, (void *)this);

    // Browser for book display
    Fl_Box *displayLabel = new Fl_Box(20, 310, 100, 25, "Books:");
    bookDisplayBrowser = new Fl_Browser(20, 335, w - 40, 150);
    bookDisplayBrowser->type(FL_HOLD_BROWSER);

    // Status output
    bookStatusOutput = new Fl_Output(20, h - 80, w - 40, 60, "Status:");

    bookManagementTab->end();

    // ============ SEARCH & SORT TAB ============
    searchSortTab = new Fl_Group(10, 35, w - 20, h - 45, "Search & Sort");

    Fl_Box *searchLabel = new Fl_Box(20, 50, 100, 25, "Search Term:");
    searchTermInput = new Fl_Input(130, 50, 250, 25);
    searchTermInput->callback(searchTermChangedCallback, (void *)this);
    searchTermInput->when(FL_WHEN_CHANGED);

    // Auto-complete suggestions browser (initially hidden)
    suggestionsBrowser = new Fl_Browser(130, 75, 250, 100);
    suggestionsBrowser->type(FL_HOLD_BROWSER);
    suggestionsBrowser->callback(suggestionClickedCallback, (void *)this);
    suggestionsBrowser->hide();

    searchByTitleBtn = new Fl_Button(20, 190, 120, 30, "Search");
    searchByTitleBtn->callback(searchByTitleCallback, (void *)this);

    sortByTitleBtn = new Fl_Button(150, 190, 120, 30, "Sort by Title");
    sortByTitleBtn->callback(sortByTitleCallback, (void *)this);

    sortByYearBtn = new Fl_Button(280, 190, 120, 30, "Sort by Year");
    sortByYearBtn->callback(sortByYearCallback, (void *)this);

    sortByAuthorBtn = new Fl_Button(410, 190, 120, 30, "Sort by Author");
    sortByAuthorBtn->callback(sortByAuthorCallback, (void *)this);

    loadAutoCompleteBtn = new Fl_Button(20, 230, 200, 30, "Refresh");
    loadAutoCompleteBtn->callback(loadAutoCompleteCallback, (void *)this);

    // Browser for search results
    Fl_Box *resultsLabel = new Fl_Box(20, 270, 100, 25, "Search Results:");
    searchResultsBrowser = new Fl_Browser(20, 295, w - 40, 150);
    searchResultsBrowser->type(FL_HOLD_BROWSER);

    // Status output
    searchStatusOutput = new Fl_Output(20, h - 80, w - 40, 60, "Status:");

    searchSortTab->end();

    // ============ BORROWER MANAGEMENT TAB ============
    borrowerTab = new Fl_Group(10, 35, w - 20, h - 45, "Borrower Management");

    // User ID and Book ID inputs
    Fl_Box *userNameLabel = new Fl_Box(20, 50, 100, 25, "User Name:");
    borrowerUserNameInput = new Fl_Input(130, 50, 160, 25);

    Fl_Box *bookBorrowTitleLabel = new Fl_Box(20, 85, 100, 25, "Book Title:");
    borrowerBookTitleInput = new Fl_Input(130, 85, 200, 25);

    Fl_Box *borrowDateLabel = new Fl_Box(20, 120, 80, 25, "Date:");
    borrowerDateInput = new Fl_Input(110, 120, 150, 25);
    // Set today's date automatically
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char dateStr[11];
    sprintf(dateStr, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    borrowerDateInput->value(dateStr);

    // Borrow and Return buttons
    borrowBookBtn = new Fl_Button(20, 160, 90, 30, "Borrow Book");
    borrowBookBtn->callback(borrowBookCallback, (void *)this);

    returnBookBtn = new Fl_Button(120, 160, 90, 30, "Return Book");
    returnBookBtn->callback(returnBookCallback, (void *)this);

    // Query buttons
    viewUserBorrowsBtn = new Fl_Button(20, 200, 150, 30, "View User's Borrows");
    viewUserBorrowsBtn->callback(viewUserBorrowsCallback, (void *)this);

    viewBookBorrowersBtn = new Fl_Button(180, 200, 150, 30, "View Book's Borrower");
    viewBookBorrowersBtn->callback(viewBookBorrowersCallback, (void *)this);

    viewHistoryBtn = new Fl_Button(340, 200, 110, 30, "View History");
    viewHistoryBtn->callback(viewHistoryCallback, (void *)this);

    loadBorrowRecordsBtn = new Fl_Button(460, 200, 130, 30, "Refresh");
    loadBorrowRecordsBtn->callback(loadBorrowRecordsCallback, (void *)this);

    // Results browser
    Fl_Box *borrowerResultsLabel = new Fl_Box(20, 240, 100, 25, "Results:");
    borrowerResultsBrowser = new Fl_Browser(20, 265, w - 40, 120);
    borrowerResultsBrowser->type(FL_HOLD_BROWSER);

    // History browser
    Fl_Box *historyLabel = new Fl_Box(20, 395, 100, 25, "History:");
    borrowerHistoryBrowser = new Fl_Browser(20, 420, w - 40, 100);
    borrowerHistoryBrowser->type(FL_HOLD_BROWSER);

    // Status output
    borrowerStatusOutput = new Fl_Output(20, h - 80, w - 40, 60, "Status:");

    borrowerTab->end();

    tabs->end();

    end();
}

LibraryGUI::~LibraryGUI()
{
    delete bookManager;
    delete searchAndSort;
    delete borrower;
}

void LibraryGUI::refreshBookDisplay()
{
    bookDisplayBrowser->clear();
    auto allBooks = bookManager->getAllBooks();

    for (const auto &entry : allBooks)
    {
        const Book &book = entry.second;
        std::string bookInfo = std::to_string(book.getId()) + " | " +
                               book.getTitle() + " | " +
                               book.getAuthor() + " | " +
                               std::to_string(book.getYear());
        bookDisplayBrowser->add(bookInfo.c_str());
    }
}

void LibraryGUI::updateStatusMessage(const std::string &message)
{
    bookStatusOutput->value(message.c_str());
}

void LibraryGUI::updateSearchStatus(const std::string &message)
{
    searchStatusOutput->value(message.c_str());
}

// ============ BOOK MANAGEMENT CALLBACKS ============

void LibraryGUI::addBookCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleAddBook();
}

void LibraryGUI::updateBookCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleUpdateBook();
}

void LibraryGUI::deleteBookCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleDeleteBook();
}

void LibraryGUI::searchBookCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleSearchBook();
}

void LibraryGUI::loadBooksCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleLoadBooks();
}

void LibraryGUI::saveBooksCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleSaveBooks();
}

void LibraryGUI::displayAllBooksCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleDisplayAllBooks();
}

// ============ BOOK MANAGEMENT HANDLERS ============

void LibraryGUI::handleAddBook()
{
    try
    {
        int id = std::stoi(bookIdInput->value());
        std::string title = bookTitleInput->value();
        std::string author = bookAuthorInput->value();
        int year = std::stoi(bookYearInput->value());
        std::string publisher = bookPublisherInput->value();

        if (title.empty() || author.empty() || publisher.empty())
        {
            updateStatusMessage("Error: All fields required!");
            return;
        }

        bookManager->addBook(id, title, author, year, publisher);
        searchAndSort->addToAutoComplete(title);

        updateStatusMessage("Book added successfully!");
        refreshBookDisplay();

        // Clear inputs
        bookIdInput->value("");
        bookTitleInput->value("");
        bookAuthorInput->value("");
        bookYearInput->value("");
        bookPublisherInput->value("");
    }
    catch (const std::exception &e)
    {
        updateStatusMessage("Error: Invalid input format!");
    }
}

void LibraryGUI::handleUpdateBook()
{
    try
    {
        int id = std::stoi(bookIdInput->value());
        std::string title = bookTitleInput->value();
        std::string author = bookAuthorInput->value();
        int year = std::stoi(bookYearInput->value());

        if (title.empty() || author.empty())
        {
            updateStatusMessage("Error: Title and Author required!");
            return;
        }

        if (bookManager->updateBook(id, title, author, year))
        {
            updateStatusMessage("Book updated successfully!");
            refreshBookDisplay();
        }
        else
        {
            updateStatusMessage("Error: Book ID not found!");
        }
    }
    catch (const std::exception &e)
    {
        updateStatusMessage("Error: Invalid input format!");
    }
}

void LibraryGUI::handleDeleteBook()
{
    try
    {
        int id = std::stoi(bookIdInput->value());

        if (bookManager->deleteBook(id))
        {
            updateStatusMessage("Book deleted successfully!");
            refreshBookDisplay();
            bookIdInput->value("");
        }
        else
        {
            updateStatusMessage("Error: Book ID not found!");
        }
    }
    catch (const std::exception &e)
    {
        updateStatusMessage("Error: Invalid Book ID!");
    }
}

void LibraryGUI::handleSearchBook()
{
    std::string searchTitle = bookTitleInput->value();

    if (searchTitle.empty())
    {
        updateStatusMessage("Error: Enter a title to search!");
        return;
    }

    auto results = bookManager->searchBookByTitle(searchTitle);

    bookDisplayBrowser->clear();

    if (results.empty())
    {
        updateStatusMessage("No books found with title: " + searchTitle);
        return;
    }

    // Display all matching books in the browser
    for (const auto &book : results)
    {
        std::string bookInfo = std::to_string(book.getId()) + " | " +
                               book.getTitle() + " | " +
                               book.getAuthor() + " | " +
                               std::to_string(book.getYear());
        bookDisplayBrowser->add(bookInfo.c_str());
    }

    // If only one result, populate the fields
    if (results.size() == 1)
    {
        const Book &book = results[0];
        bookIdInput->value(std::to_string(book.getId()).c_str());
        bookTitleInput->value(book.getTitle().c_str());
        bookAuthorInput->value(book.getAuthor().c_str());
        bookYearInput->value(std::to_string(book.getYear()).c_str());
        bookPublisherInput->value(book.getPublisher().c_str());
    }

    std::string statusMsg = "Found " + std::to_string(results.size()) + " book(s) matching: " + searchTitle;
    updateStatusMessage(statusMsg);
}

void LibraryGUI::handleLoadBooks()
{
    bookManager->loadBooksFromCSV("./data/book.csv");
    searchAndSort->loadAllBooksToTrie();
    updateStatusMessage("Books loaded from CSV!");
    refreshBookDisplay();
}

void LibraryGUI::handleSaveBooks()
{
    bookManager->saveBooksToCSV("./data/book.csv");
    updateStatusMessage("Books saved to CSV!");
}

void LibraryGUI::handleDisplayAllBooks()
{
    refreshBookDisplay();
    updateStatusMessage("Displaying all books in database!");
}

// ============ SEARCH & SORT CALLBACKS ============

void LibraryGUI::searchByTitleCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleSearchByTitle();
}

void LibraryGUI::sortByTitleCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleSortByTitle();
}

void LibraryGUI::sortByYearCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleSortByYear();
}

void LibraryGUI::sortByAuthorCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleSortByAuthor();
}

void LibraryGUI::loadAutoCompleteCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleLoadAutoComplete();
}

// ============ SEARCH & SORT HANDLERS ============

void LibraryGUI::handleSearchByTitle()
{
    std::string searchTerm = searchTermInput->value();

    if (searchTerm.empty())
    {
        updateSearchStatus("Error: Enter a search term!");
        return;
    }

    auto results = searchAndSort->searchBooksByTitle(searchTerm);

    searchResultsBrowser->clear();
    if (results.empty())
    {
        updateSearchStatus("No books found matching: " + searchTerm);
        return;
    }

    for (const auto &book : results)
    {
        std::string bookInfo = std::to_string(book.getId()) + " | " +
                               book.getTitle() + " | " +
                               book.getAuthor() + " | " +
                               std::to_string(book.getYear());
        searchResultsBrowser->add(bookInfo.c_str());
    }

    std::string statusMsg = "Found " + std::to_string(results.size()) + " book(s)!";
    updateSearchStatus(statusMsg);
}

void LibraryGUI::handleSortByTitle()
{
    auto allBooks = bookManager->getAllBooks();

    if (allBooks.empty())
    {
        updateSearchStatus("No books to sort!");
        return;
    }

    // Create array of Book pointers
    Book **booksArray = new Book *[allBooks.size()];
    int i = 0;
    for (auto &entry : allBooks)
    {
        booksArray[i++] = &entry.second;
    }

    // Sort by title
    searchAndSort->sortBooksByTitle(booksArray, allBooks.size());

    // Display sorted results
    searchResultsBrowser->clear();
    for (size_t j = 0; j < allBooks.size(); j++)
    {
        std::string bookInfo = std::to_string(booksArray[j]->getId()) + " | " +
                               booksArray[j]->getTitle() + " | " +
                               booksArray[j]->getAuthor() + " | " +
                               std::to_string(booksArray[j]->getYear());
        searchResultsBrowser->add(bookInfo.c_str());
    }

    delete[] booksArray;
    updateSearchStatus("Books sorted by title!");
}

void LibraryGUI::handleSortByYear()
{
    auto allBooks = bookManager->getAllBooks();

    if (allBooks.empty())
    {
        updateSearchStatus("No books to sort!");
        return;
    }

    // Create array of Book pointers
    Book **booksArray = new Book *[allBooks.size()];
    int i = 0;
    for (auto &entry : allBooks)
    {
        booksArray[i++] = &entry.second;
    }

    // Sort by year
    searchAndSort->sortBooksByYear(booksArray, allBooks.size());

    // Display sorted results
    searchResultsBrowser->clear();
    for (size_t j = 0; j < allBooks.size(); j++)
    {
        std::string bookInfo = std::to_string(booksArray[j]->getId()) + " | " +
                               booksArray[j]->getTitle() + " | " +
                               booksArray[j]->getAuthor() + " | " +
                               std::to_string(booksArray[j]->getYear());
        searchResultsBrowser->add(bookInfo.c_str());
    }

    delete[] booksArray;
    updateSearchStatus("Books sorted by year!");
}

void LibraryGUI::handleSortByAuthor()
{
    auto allBooks = bookManager->getAllBooks();

    if (allBooks.empty())
    {
        updateSearchStatus("No books to sort!");
        return;
    }

    // Create array of Book pointers
    Book **booksArray = new Book *[allBooks.size()];
    int i = 0;
    for (auto &entry : allBooks)
    {
        booksArray[i++] = &entry.second;
    }

    // Sort by author
    searchAndSort->sortBooksByAuthor(booksArray, allBooks.size());

    // Display sorted results
    searchResultsBrowser->clear();
    for (size_t j = 0; j < allBooks.size(); j++)
    {
        std::string bookInfo = std::to_string(booksArray[j]->getId()) + " | " +
                               booksArray[j]->getTitle() + " | " +
                               booksArray[j]->getAuthor() + " | " +
                               std::to_string(booksArray[j]->getYear());
        searchResultsBrowser->add(bookInfo.c_str());
    }

    delete[] booksArray;
    updateSearchStatus("Books sorted by author!");
}

void LibraryGUI::handleLoadAutoComplete()
{
    searchAndSort->loadAllBooksToTrie();
    updateSearchStatus("Auto-complete loaded with all book titles!");
}

void LibraryGUI::searchTermChangedCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->showAutoCompleteSuggestions(gui->searchTermInput->value());
}

void LibraryGUI::showAutoCompleteSuggestions(const std::string &prefix)
{
    if (prefix.empty())
    {
        suggestionsBrowser->hide();
        return;
    }

    // Get auto-complete suggestions from Trie
    auto suggestions = searchAndSort->autoComplete(prefix);

    if (suggestions.empty())
    {
        suggestionsBrowser->hide();
        return;
    }

    // Show suggestions in browser
    suggestionsBrowser->clear();
    for (const auto &suggestion : suggestions)
    {
        suggestionsBrowser->add(suggestion.c_str());
    }

    suggestionsBrowser->show();
    redraw();
}

void LibraryGUI::suggestionClickedCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleSuggestionClick();
}

void LibraryGUI::handleSuggestionClick()
{
    int selected = suggestionsBrowser->value();
    if (selected > 0)
    {
        const char *selectedText = suggestionsBrowser->text(selected);
        if (selectedText)
        {
            searchTermInput->value(selectedText);
            suggestionsBrowser->hide();
            redraw();
        }
    }
}

void LibraryGUI::updateBorrowerStatus(const std::string &message)
{
    borrowerStatusOutput->value(message.c_str());
}

// ============ BORROWER CALLBACKS ============

void LibraryGUI::borrowBookCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleBorrowBook();
}

void LibraryGUI::returnBookCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleReturnBook();
}

void LibraryGUI::viewUserBorrowsCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleViewUserBorrows();
}

void LibraryGUI::viewBookBorrowersCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleViewBookBorrowers();
}

void LibraryGUI::viewHistoryCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleViewHistory();
}

void LibraryGUI::loadBorrowRecordsCallback(Fl_Widget *w, void *data)
{
    LibraryGUI *gui = (LibraryGUI *)data;
    gui->handleLoadBorrowRecords();
}

// ============ BORROWER HANDLERS ============

void LibraryGUI::handleBorrowBook()
{
    try
    {
        std::string userName = borrowerUserNameInput->value();
        std::string bookTitle = borrowerBookTitleInput->value();
        std::string date = borrowerDateInput->value();

        if (userName.empty() || bookTitle.empty() || date.empty())
        {
            updateBorrowerStatus("Error: Enter user and book title!");
            return;
        }

        // Verify book exists by title
        {
            auto matches = bookManager->searchBookByTitle(bookTitle);
            if (matches.empty())
            {
                updateBorrowerStatus("Error: Book title not found!");
                return;
            }
        }

        if (borrower->borrowBook(userName, bookTitle, date))
        {
            updateBorrowerStatus("Book borrowed successfully!");
            borrowerUserNameInput->value("");
            borrowerBookTitleInput->value("");
            // Reset to today's date
            time_t now = time(0);
            tm *ltm = localtime(&now);
            char dateStr[11];
            sprintf(dateStr, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
            borrowerDateInput->value(dateStr);
        }
        else
        {
            updateBorrowerStatus("Error: Could not borrow book!");
        }
    }
    catch (const std::exception &e)
    {
        updateBorrowerStatus("Error: Invalid input format!");
    }
}

void LibraryGUI::handleReturnBook()
{
    try
    {
        std::string userName = borrowerUserNameInput->value();
        std::string bookTitle = borrowerBookTitleInput->value();
        std::string date = borrowerDateInput->value();

        if (userName.empty() || bookTitle.empty() || date.empty())
        {
            updateBorrowerStatus("Error: Enter user and book title!");
            return;
        }

        if (borrower->returnBook(userName, bookTitle, date))
        {
            updateBorrowerStatus("Book returned successfully!");
            borrowerUserNameInput->value("");
            borrowerBookTitleInput->value("");
            // Reset to today's date
            time_t now = time(0);
            tm *ltm = localtime(&now);
            char dateStr[11];
            sprintf(dateStr, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
            borrowerDateInput->value(dateStr);
        }
        else
        {
            updateBorrowerStatus("Error: Could not return book!");
        }
    }
    catch (const std::exception &e)
    {
        updateBorrowerStatus("Error: Invalid input format!");
    }
}

void LibraryGUI::handleViewUserBorrows()
{
    try
    {
        std::string userName = borrowerUserNameInput->value();

        auto borrowsList = borrower->getUserActiveBorrows(userName);

        borrowerResultsBrowser->clear();

        if (borrowsList == nullptr)
        {
            updateBorrowerStatus("User has no active borrows.");
            return;
        }
        borrowerResultsBrowser->add("Active Borrows:");
        for (const auto &entry : borrowsList->toVector())
        {
            borrowerResultsBrowser->add(entry.c_str());
        }
        std::string statusMsg = "Displaying active borrows for User '" + userName + "'";
        updateBorrowerStatus(statusMsg);
    }
    catch (const std::exception &e)
    {
        updateBorrowerStatus("Error: Invalid User ID!");
    }
}

void LibraryGUI::handleViewBookBorrowers()
{
    try
    {
        std::string bookTitle = borrowerBookTitleInput->value();

        auto borrowersList = borrower->getBookActiveBorrowers(bookTitle);

        borrowerResultsBrowser->clear();

        if (borrowersList == nullptr)
        {
            updateBorrowerStatus("Book has no active borrower.");
            return;
        }
        borrowerResultsBrowser->add("Active Borrower:");
        for (const auto &entry : borrowersList->toVector())
        {
            borrowerResultsBrowser->add(entry.c_str());
        }
        std::string statusMsg = "Displaying active borrower for Book '" + bookTitle + "'";
        updateBorrowerStatus(statusMsg);
    }
    catch (const std::exception &e)
    {
        updateBorrowerStatus("Error: Invalid Book ID!");
    }
}

void LibraryGUI::handleViewHistory()
{
    borrowerHistoryBrowser->clear();
    updateBorrowerStatus("Displaying complete borrow/return history...");
    auto histList = borrower->getHistory();
    if (histList)
    {
        for (const auto &entry : histList->toVector())
        {
            borrowerHistoryBrowser->add(entry.c_str());
        }
    }
}

void LibraryGUI::handleLoadBorrowRecords()
{
    borrower->loadBorrowRecordsFromCSV("D:/HP/Projects/DSAE/Optimized-Library-Lookup-System/data/borrow_records.csv");
    updateBorrowerStatus("Borrow records loaded from CSV!");
}
