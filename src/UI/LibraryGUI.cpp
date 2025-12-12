#include "LibraryGUI.h"
#include <QMessageBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QDate>
#include <sstream>
#include <algorithm>

LibraryGUI::LibraryGUI(QWidget *parent)
    : QMainWindow(parent)
{
    // Initialize managers
    bookManager = new BookManager();
    searchAndSort = new SearchAndSort(bookManager);
    borrower = new Borrower("D:/HP/Projects/DSAE/Optimized-Library-Lookup-System/data/borrow_records.csv");

    // Link borrower with book manager
    borrower->setBookManager(bookManager);

    // Load initial data
    bookManager->loadBooksFromCSV("D:/HP/Projects/DSAE/Optimized-Library-Lookup-System/data/book.csv");
    searchAndSort->loadAllBooksToTrie();
    borrower->loadBorrowRecordsFromCSV("D:/HP/Projects/DSAE/Optimized-Library-Lookup-System/data/borrow_records.csv");

    // Setup UI
    setupUI();

    // Set window properties
    setWindowTitle("Dsa Enabled Library lookup");
    resize(1400, 900);

    // Apply global stylesheet
    setStyleSheet(
        "QMainWindow {"
        "   background-color: #f6f8fa;"
        "}"
        "QTabWidget::pane {"
        "   border: 1px solid #d0d7de;"
        "   background: white;"
        "   border-radius: 6px;"
        "}"
        "QTabBar::tab {"
        "   background: #f6f8fa;"
        "   border: 1px solid #d0d7de;"
        "   padding: 8px 16px;"
        "   margin-right: 4px;"
        "   border-top-left-radius: 6px;"
        "   border-top-right-radius: 6px;"
        "   font-weight: 500;"
        "}"
        "QTabBar::tab:selected {"
        "   background: white;"
        "   border-bottom-color: white;"
        "}"
        "QTabBar::tab:hover {"
        "   background: #e8eaed;"
        "}"
        "QLineEdit {"
        "   padding: 8px 12px;"
        "   border: 1px solid #d0d7de;"
        "   border-radius: 6px;"
        "   background: white;"
        "   font-size: 14px;"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #0969da;"
        "   outline: none;"
        "}"
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                               stop:0 #0969da, stop:1 #0860ca);"
        "   color: white;"
        "   border: 1px solid #0860ca;"
        "   padding: 8px 16px;"
        "   border-radius: 6px;"
        "   font-weight: 600;"
        "   font-size: 14px;"
        "   min-width: 80px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                               stop:0 #0860ca, stop:1 #0757b3);"
        "   border: 1px solid #0757b3;"
        "}"
        "QPushButton:pressed {"
        "   background: #0757b3;"
        "}"
        "QListWidget {"
        "   border: 1px solid #d0d7de;"
        "   border-radius: 6px;"
        "   background: white;"
        "   padding: 8px;"
        "   font-size: 13px;"
        "}"
        "QListWidget::item {"
        "   padding: 2px 6px;"
        "   border-bottom: 1px solid #f6f8fa;"
        "   min-height: 18px;"
        "   max-height: 24px;"
        "}"
        "QListWidget::item:selected {"
        "   background: #ddf4ff;"
        "   color: #0969da;"
        "}"
        "QListWidget::item:hover {"
        "   background: #f6f8fa;"
        "}"
        "QLabel {"
        "   color: #24292f;"
        "   font-size: 13px;"
        "}"
        "QGroupBox {"
        "   border: 1px solid #d0d7de;"
        "   border-radius: 6px;"
        "   margin-top: 6px;"
        "   padding-top: 6px;"
        "   background: white;"
        "   font-weight: 600;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top left;"
        "   padding: 0 8px;"
        "   color: #24292f;"
        "}");
}

LibraryGUI::~LibraryGUI()
{
    delete bookManager;
    delete searchAndSort;
    delete borrower;
}

void LibraryGUI::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(12);

    // Create tab widget
    tabWidget = new QTabWidget(this);

    // Create tabs
    bookManagementTab = createBookManagementTab();
    searchSortTab = createSearchSortTab();
    borrowerTab = createBorrowerTab();

    // Add tabs
    tabWidget->addTab(bookManagementTab, "Book Management");
    tabWidget->addTab(searchSortTab, "Search & Sort");
    tabWidget->addTab(borrowerTab, "Borrowing");

    mainLayout->addWidget(tabWidget);
}

QWidget *LibraryGUI::createBookManagementTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(12);

    // Input group
    QGroupBox *inputGroup = new QGroupBox(QString::fromUtf8("📝 Book Information"));
    QFormLayout *formLayout = new QFormLayout(inputGroup);
    formLayout->setSpacing(8);
    formLayout->setContentsMargins(12, 12, 12, 12);

    bookIdInput = new QLineEdit();
    bookIdInput->setPlaceholderText("Enter book ID (number)");
    bookTitleInput = new QLineEdit();
    bookTitleInput->setPlaceholderText("Enter book title");
    bookAuthorInput = new QLineEdit();
    bookAuthorInput->setPlaceholderText("Enter author name");
    bookYearInput = new QLineEdit();
    bookYearInput->setPlaceholderText("Enter publication year");
    bookPublisherInput = new QLineEdit();
    bookPublisherInput->setPlaceholderText("Enter publisher name");

    formLayout->addRow("Book ID:", bookIdInput);
    formLayout->addRow("Title:", bookTitleInput);
    formLayout->addRow("Author:", bookAuthorInput);
    formLayout->addRow("Year:", bookYearInput);
    formLayout->addRow("Publisher:", bookPublisherInput);

    layout->addWidget(inputGroup);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(8);

    addBookBtn = new QPushButton("Add Book");
    updateBookBtn = new QPushButton("Update");
    deleteBookBtn = new QPushButton("Delete");
    searchBookBtn = new QPushButton("Search ID");

    buttonLayout->addWidget(addBookBtn);
    buttonLayout->addWidget(updateBookBtn);
    buttonLayout->addWidget(deleteBookBtn);
    buttonLayout->addWidget(searchBookBtn);
    buttonLayout->addStretch();

    layout->addLayout(buttonLayout);

    // File operations
    QHBoxLayout *fileLayout = new QHBoxLayout();
    fileLayout->setSpacing(8);

    loadBooksBtn = new QPushButton("Load CSV");
    saveBooksBtn = new QPushButton("Save CSV");
    displayAllBooksBtn = new QPushButton("Display All");

    fileLayout->addWidget(loadBooksBtn);
    fileLayout->addWidget(saveBooksBtn);
    fileLayout->addWidget(displayAllBooksBtn);
    fileLayout->addStretch();

    layout->addLayout(fileLayout);

    // Display area
    QGroupBox *displayGroup = new QGroupBox("Books Display");
    QVBoxLayout *displayLayout = new QVBoxLayout(displayGroup);
    displayLayout->setContentsMargins(8, 8, 8, 8);

    bookDisplayList = new QListWidget();
    displayLayout->addWidget(bookDisplayList);

    layout->addWidget(displayGroup);

    // Status label
    bookStatusLabel = new QLabel(QString::fromUtf8("✅ Ready"));
    bookStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
    layout->addWidget(bookStatusLabel);

    // Connect signals
    connect(addBookBtn, &QPushButton::clicked, this, &LibraryGUI::handleAddBook);
    connect(updateBookBtn, &QPushButton::clicked, this, &LibraryGUI::handleUpdateBook);
    connect(deleteBookBtn, &QPushButton::clicked, this, &LibraryGUI::handleDeleteBook);
    connect(searchBookBtn, &QPushButton::clicked, this, &LibraryGUI::handleSearchBook);
    connect(loadBooksBtn, &QPushButton::clicked, this, &LibraryGUI::handleLoadBooks);
    connect(saveBooksBtn, &QPushButton::clicked, this, &LibraryGUI::handleSaveBooks);
    connect(displayAllBooksBtn, &QPushButton::clicked, this, &LibraryGUI::handleDisplayAllBooks);

    return tab;
}

QWidget *LibraryGUI::createSearchSortTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(12);

    // Search input group
    QGroupBox *searchGroup = new QGroupBox("Search");
    QVBoxLayout *searchLayout = new QVBoxLayout(searchGroup);
    searchLayout->setContentsMargins(12, 12, 12, 12);
    searchLayout->setSpacing(8);

    searchTermInput = new QLineEdit();
    searchTermInput->setPlaceholderText("Type to search or get suggestions...");
    searchLayout->addWidget(searchTermInput);

    // Auto-complete suggestions
    QLabel *suggestionLabel = new QLabel("Suggestions:");
    suggestionLabel->setStyleSheet("QLabel { font-weight: 600; margin-top: 8px; }");
    searchLayout->addWidget(suggestionLabel);

    suggestionsList = new QListWidget();
    suggestionsList->setMaximumHeight(100);
    searchLayout->addWidget(suggestionsList);

    layout->addWidget(searchGroup);

    // Search and sort buttons
    QHBoxLayout *actionLayout = new QHBoxLayout();
    actionLayout->setSpacing(8);

    searchByTitleBtn = new QPushButton("Search by Title");
    sortByTitleBtn = new QPushButton("Sort by Title");
    sortByYearBtn = new QPushButton("Sort by Year");
    sortByAuthorBtn = new QPushButton("Sort by Author");
    loadAutoCompleteBtn = new QPushButton("Reload Trie");

    actionLayout->addWidget(searchByTitleBtn);
    actionLayout->addWidget(sortByTitleBtn);
    actionLayout->addWidget(sortByYearBtn);
    actionLayout->addWidget(sortByAuthorBtn);
    actionLayout->addWidget(loadAutoCompleteBtn);
    actionLayout->addStretch();

    layout->addLayout(actionLayout);

    // Results display
    QGroupBox *resultsGroup = new QGroupBox("Search Results");
    QVBoxLayout *resultsLayout = new QVBoxLayout(resultsGroup);
    resultsLayout->setContentsMargins(8, 8, 8, 8);

    searchResultsList = new QListWidget();
    resultsLayout->addWidget(searchResultsList);

    layout->addWidget(resultsGroup);

    // Status label
    searchStatusLabel = new QLabel(QString::fromUtf8("✅ Ready"));
    searchStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
    layout->addWidget(searchStatusLabel);

    // Connect signals
    connect(searchTermInput, &QLineEdit::textChanged, this, &LibraryGUI::handleSearchTermChanged);
    connect(suggestionsList, &QListWidget::itemClicked, this, &LibraryGUI::handleSuggestionClick);
    connect(searchByTitleBtn, &QPushButton::clicked, this, &LibraryGUI::handleSearchByTitle);
    connect(sortByTitleBtn, &QPushButton::clicked, this, &LibraryGUI::handleSortByTitle);
    connect(sortByYearBtn, &QPushButton::clicked, this, &LibraryGUI::handleSortByYear);
    connect(sortByAuthorBtn, &QPushButton::clicked, this, &LibraryGUI::handleSortByAuthor);
    connect(loadAutoCompleteBtn, &QPushButton::clicked, this, &LibraryGUI::handleLoadAutoComplete);

    return tab;
}

QWidget *LibraryGUI::createBorrowerTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(12);

    // Borrowing input group
    QGroupBox *inputGroup = new QGroupBox(QString::fromUtf8("📝 Borrow/Return Information"));
    inputGroup->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    QFormLayout *formLayout = new QFormLayout(inputGroup);
    formLayout->setSpacing(8);
    formLayout->setContentsMargins(12, 12, 12, 12);
    formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);

    borrowerUserNameInput = new QLineEdit();
    borrowerUserNameInput->setPlaceholderText("Enter user name");
    borrowerBookTitleInput = new QLineEdit();
    borrowerBookTitleInput->setPlaceholderText("Enter book title");
    borrowerDateInput = new QLineEdit();
    borrowerDateInput->setPlaceholderText("YYYY-MM-DD");

    // Auto-populate with current date
    QDate currentDate = QDate::currentDate();
    borrowerDateInput->setText(currentDate.toString("yyyy-MM-dd"));

    formLayout->addRow("User Name:", borrowerUserNameInput);
    formLayout->addRow("Book Title:", borrowerBookTitleInput);
    formLayout->addRow("Date:", borrowerDateInput);

    layout->addWidget(inputGroup);

    // Action buttons
    QHBoxLayout *actionLayout = new QHBoxLayout();
    actionLayout->setSpacing(8);

    borrowBookBtn = new QPushButton("Borrow Book");
    returnBookBtn = new QPushButton("Return Book");
    loadBorrowRecordsBtn = new QPushButton("Load Records");

    actionLayout->addWidget(borrowBookBtn);
    actionLayout->addWidget(returnBookBtn);
    actionLayout->addWidget(loadBorrowRecordsBtn);
    actionLayout->addStretch();

    layout->addLayout(actionLayout);

    // View buttons
    QHBoxLayout *viewLayout = new QHBoxLayout();
    viewLayout->setSpacing(8);

    viewUserBorrowsBtn = new QPushButton("View User Borrows");
    viewBookBorrowersBtn = new QPushButton("View Book Borrowers");
    viewHistoryBtn = new QPushButton("View History");

    viewLayout->addWidget(viewUserBorrowsBtn);
    viewLayout->addWidget(viewBookBorrowersBtn);
    viewLayout->addWidget(viewHistoryBtn);
    viewLayout->addStretch();

    layout->addLayout(viewLayout);

    // Results display
    QGroupBox *resultsGroup = new QGroupBox("Active Borrows");
    QVBoxLayout *resultsLayout = new QVBoxLayout(resultsGroup);
    resultsLayout->setContentsMargins(8, 8, 8, 8);

    borrowerResultsList = new QListWidget();
    resultsLayout->addWidget(borrowerResultsList);

    layout->addWidget(resultsGroup);

    // History display
    QGroupBox *historyGroup = new QGroupBox(QString::fromUtf8("📜 Borrow History"));
    QVBoxLayout *historyLayout = new QVBoxLayout(historyGroup);
    historyLayout->setContentsMargins(8, 8, 8, 8);

    borrowerHistoryList = new QListWidget();
    historyLayout->addWidget(borrowerHistoryList);

    layout->addWidget(historyGroup);

    // Status label
    borrowerStatusLabel = new QLabel(QString::fromUtf8("✅ Ready"));
    borrowerStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
    layout->addWidget(borrowerStatusLabel);

    // Connect signals
    connect(borrowBookBtn, &QPushButton::clicked, this, &LibraryGUI::handleBorrowBook);
    connect(returnBookBtn, &QPushButton::clicked, this, &LibraryGUI::handleReturnBook);
    connect(viewUserBorrowsBtn, &QPushButton::clicked, this, &LibraryGUI::handleViewUserBorrows);
    connect(viewBookBorrowersBtn, &QPushButton::clicked, this, &LibraryGUI::handleViewBookBorrowers);
    connect(viewHistoryBtn, &QPushButton::clicked, this, &LibraryGUI::handleViewHistory);
    connect(loadBorrowRecordsBtn, &QPushButton::clicked, this, &LibraryGUI::handleLoadBorrowRecords);

    return tab;
}

// Book Management Handlers
void LibraryGUI::handleAddBook()
{
    try
    {
        int id = std::stoi(bookIdInput->text().toStdString());
        std::string title = bookTitleInput->text().toStdString();
        std::string author = bookAuthorInput->text().toStdString();
        int year = std::stoi(bookYearInput->text().toStdString());
        std::string publisher = bookPublisherInput->text().toStdString();

        if (publisher.empty())
        {
            publisher = "Unknown";
        }

        bookManager->addBook(id, title, author, year, publisher);
        searchAndSort->addToAutoComplete(title);

        updateStatusMessage("✅ Book added successfully!");
        bookStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");

        // Clear inputs
        bookIdInput->clear();
        bookTitleInput->clear();
        bookAuthorInput->clear();
        bookYearInput->clear();
        bookPublisherInput->clear();

        refreshBookDisplay();
    }
    catch (const std::exception &e)
    {
        updateStatusMessage("❌ Error: Invalid input. Please check ID and Year are numbers.");
        bookStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
    }
}

void LibraryGUI::handleUpdateBook()
{
    try
    {
        int id = std::stoi(bookIdInput->text().toStdString());
        std::string newTitle = bookTitleInput->text().toStdString();
        std::string newAuthor = bookAuthorInput->text().toStdString();
        int newYear = std::stoi(bookYearInput->text().toStdString());

        bool success = bookManager->updateBook(id, newTitle, newAuthor, newYear);

        if (success)
        {
            updateStatusMessage("✅ Book updated successfully!");
            bookStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
            refreshBookDisplay();
        }
        else
        {
            updateStatusMessage("❌ Book not found!");
            bookStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
        }
    }
    catch (const std::exception &e)
    {
        updateStatusMessage("❌ Error: Invalid input. Please check ID and Year are numbers.");
        bookStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
    }
}

void LibraryGUI::handleDeleteBook()
{
    try
    {
        int id = std::stoi(bookIdInput->text().toStdString());
        bool success = bookManager->deleteBook(id);

        if (success)
        {
            updateStatusMessage("✅ Book deleted successfully!");
            bookStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
            bookIdInput->clear();
            refreshBookDisplay();
        }
        else
        {
            updateStatusMessage("❌ Book not found!");
            bookStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
        }
    }
    catch (const std::exception &e)
    {
        updateStatusMessage("❌ Error: Invalid book ID.");
        bookStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
    }
}

void LibraryGUI::handleSearchBook()
{
    try
    {
        int id = std::stoi(bookIdInput->text().toStdString());
        Book *book = bookManager->searchBook(id);

        if (book)
        {
            bookDisplayList->clear();
            std::stringstream ss;
            ss << "📖 ID: " << book->getId()
               << " | Title: " << book->getTitle()
               << " | Author: " << book->getAuthor()
               << " | Year: " << book->getYear()
               << " | Publisher: " << book->getPublisher();

            bookDisplayList->addItem(QString::fromStdString(ss.str()));
            updateStatusMessage("✅ Book found!");
            bookStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");

            // Populate fields
            bookTitleInput->setText(QString::fromStdString(book->getTitle()));
            bookAuthorInput->setText(QString::fromStdString(book->getAuthor()));
            bookYearInput->setText(QString::number(book->getYear()));
            bookPublisherInput->setText(QString::fromStdString(book->getPublisher()));
        }
        else
        {
            bookDisplayList->clear();
            updateStatusMessage("❌ Book not found!");
            bookStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
        }
    }
    catch (const std::exception &e)
    {
        updateStatusMessage("❌ Error: Invalid book ID.");
        bookStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
    }
}

void LibraryGUI::handleLoadBooks()
{
    try
    {
        bookManager->loadBooksFromCSV("D:/HP/Projects/DSAE/Optimized-Library-Lookup-System/data/book.csv");
        searchAndSort->loadAllBooksToTrie();
        updateStatusMessage("✅ Books loaded from CSV successfully!");
        bookStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
        refreshBookDisplay();
    }
    catch (const std::exception &e)
    {
        updateStatusMessage("❌ Error loading books from CSV!");
        bookStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
    }
}

void LibraryGUI::handleSaveBooks()
{
    try
    {
        bookManager->saveBooksToCSV("D:/HP/Projects/DSAE/Optimized-Library-Lookup-System/data/book.csv");
        updateStatusMessage("✅ Books saved to CSV successfully!");
        bookStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
    }
    catch (const std::exception &e)
    {
        updateStatusMessage("❌ Error saving books to CSV!");
        bookStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
    }
}

void LibraryGUI::handleDisplayAllBooks()
{
    refreshBookDisplay();
    updateStatusMessage("✅ Displaying all books.");
    bookStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
}

// Search & Sort Handlers
void LibraryGUI::handleSearchByTitle()
{
    std::string searchTerm = searchTermInput->text().toStdString();

    if (searchTerm.empty())
    {
        updateSearchStatus("⚠️ Please enter a search term.");
        searchStatusLabel->setStyleSheet("QLabel { color: #9a6700; font-weight: 600; }");
        return;
    }

    std::vector<Book> results = searchAndSort->searchBooksByTitle(searchTerm);

    searchResultsList->clear();

    if (results.empty())
    {
        searchResultsList->addItem(QString::fromUtf8("❌ No books found matching the search term."));
        updateSearchStatus("❌ No results found.");
        searchStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
    }
    else
    {
        for (const auto &book : results)
        {
            std::stringstream ss;
            ss << "📖 ID: " << book.getId()
               << " | Title: " << book.getTitle()
               << " | Author: " << book.getAuthor()
               << " | Year: " << book.getYear();
            searchResultsList->addItem(QString::fromStdString(ss.str()));
        }
        updateSearchStatus("✅ Found " + std::to_string(results.size()) + " book(s).");
        searchStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
    }
}

void LibraryGUI::handleSortByTitle()
{
    std::vector<std::pair<int, Book>> allBooks = bookManager->getAllBooks();

    if (allBooks.empty())
    {
        updateSearchStatus("❌ No books to sort.");
        searchStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
        return;
    }

    // Convert to array of pointers for sorting
    std::vector<Book> bookVec;
    for (const auto &pair : allBooks)
    {
        bookVec.push_back(pair.second);
    }

    // Sort using merge sort (in-place via vector)
    std::sort(bookVec.begin(), bookVec.end(), [](const Book &a, const Book &b)
              { return a.getTitle() < b.getTitle(); });

    searchResultsList->clear();
    for (const auto &book : bookVec)
    {
        std::stringstream ss;
        ss << "📖 " << book.getTitle()
           << " | Author: " << book.getAuthor()
           << " | Year: " << book.getYear()
           << " | ID: " << book.getId();
        searchResultsList->addItem(QString::fromStdString(ss.str()));
    }

    updateSearchStatus("✅ Books sorted by title.");
    searchStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
}

void LibraryGUI::handleSortByYear()
{
    std::vector<std::pair<int, Book>> allBooks = bookManager->getAllBooks();

    if (allBooks.empty())
    {
        updateSearchStatus("❌ No books to sort.");
        searchStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
        return;
    }

    std::vector<Book> bookVec;
    for (const auto &pair : allBooks)
    {
        bookVec.push_back(pair.second);
    }

    std::sort(bookVec.begin(), bookVec.end(), [](const Book &a, const Book &b)
              { return a.getYear() < b.getYear(); });

    searchResultsList->clear();
    for (const auto &book : bookVec)
    {
        std::stringstream ss;
        ss << "📅 " << book.getYear()
           << " | " << book.getTitle()
           << " | Author: " << book.getAuthor()
           << " | ID: " << book.getId();
        searchResultsList->addItem(QString::fromStdString(ss.str()));
    }

    updateSearchStatus("✅ Books sorted by year.");
    searchStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
}

void LibraryGUI::handleSortByAuthor()
{
    std::vector<std::pair<int, Book>> allBooks = bookManager->getAllBooks();

    if (allBooks.empty())
    {
        updateSearchStatus("❌ No books to sort.");
        searchStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
        return;
    }

    std::vector<Book> bookVec;
    for (const auto &pair : allBooks)
    {
        bookVec.push_back(pair.second);
    }

    std::sort(bookVec.begin(), bookVec.end(), [](const Book &a, const Book &b)
              { return a.getAuthor() < b.getAuthor(); });

    searchResultsList->clear();
    for (const auto &book : bookVec)
    {
        std::stringstream ss;
        ss << "👤 " << book.getAuthor()
           << " | " << book.getTitle()
           << " | Year: " << book.getYear()
           << " | ID: " << book.getId();
        searchResultsList->addItem(QString::fromStdString(ss.str()));
    }

    updateSearchStatus("✅ Books sorted by author.");
    searchStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
}

void LibraryGUI::handleLoadAutoComplete()
{
    searchAndSort->loadAllBooksToTrie();
    updateSearchStatus("✅ Auto-complete data reloaded from book database.");
    searchStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
}

void LibraryGUI::handleSearchTermChanged()
{
    std::string prefix = searchTermInput->text().toStdString();

    if (prefix.empty())
    {
        suggestionsList->clear();
        return;
    }

    std::vector<std::string> suggestions = searchAndSort->autoComplete(prefix);

    suggestionsList->clear();

    if (suggestions.empty())
    {
        suggestionsList->addItem(QString::fromUtf8("💡 No suggestions"));
    }
    else
    {
        for (const auto &suggestion : suggestions)
        {
            suggestionsList->addItem(QString::fromStdString("📚 " + suggestion));
        }
    }
}

void LibraryGUI::handleSuggestionClick()
{
    QListWidgetItem *item = suggestionsList->currentItem();
    if (item)
    {
        QString text = item->text();
        // Remove the emoji prefix "📚 "
        if (text.startsWith(QString::fromUtf8("📚 ")))
        {
            text = text.mid(3); // Remove first 3 characters (emoji + space)
        }
        searchTermInput->setText(text);
        handleSearchByTitle(); // Auto-search when suggestion is clicked
    }
}

// Borrower Handlers
void LibraryGUI::handleBorrowBook()
{
    std::string userName = borrowerUserNameInput->text().toStdString();
    std::string bookTitle = borrowerBookTitleInput->text().toStdString();
    std::string date = borrowerDateInput->text().toStdString();

    if (userName.empty() || bookTitle.empty() || date.empty())
    {
        updateBorrowerStatus("⚠️ Please fill in all fields.");
        borrowerStatusLabel->setStyleSheet("QLabel { color: #9a6700; font-weight: 600; }");
        return;
    }

    bool success = borrower->borrowBook(userName, bookTitle, date);

    if (success)
    {
        updateBorrowerStatus("✅ Book borrowed successfully!");
        borrowerStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");

        // Clear inputs
        borrowerUserNameInput->clear();
        borrowerBookTitleInput->clear();
        borrowerDateInput->clear();
    }
    else
    {
        updateBorrowerStatus("❌ Failed to borrow book. Book may not exist or already borrowed.");
        borrowerStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
    }
}

void LibraryGUI::handleReturnBook()
{
    std::string userName = borrowerUserNameInput->text().toStdString();
    std::string bookTitle = borrowerBookTitleInput->text().toStdString();
    std::string date = borrowerDateInput->text().toStdString();

    if (userName.empty() || bookTitle.empty() || date.empty())
    {
        updateBorrowerStatus("⚠️ Please fill in all fields.");
        borrowerStatusLabel->setStyleSheet("QLabel { color: #9a6700; font-weight: 600; }");
        return;
    }

    bool success = borrower->returnBook(userName, bookTitle, date);

    if (success)
    {
        updateBorrowerStatus("✅ Book returned successfully!");
        borrowerStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");

        // Clear inputs
        borrowerUserNameInput->clear();
        borrowerBookTitleInput->clear();
        borrowerDateInput->clear();
    }
    else
    {
        updateBorrowerStatus("❌ Failed to return book. Book may not be borrowed by this user.");
        borrowerStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
    }
}

void LibraryGUI::handleViewUserBorrows()
{
    std::string userName = borrowerUserNameInput->text().toStdString();

    if (userName.empty())
    {
        updateBorrowerStatus("⚠️ Please enter a user name.");
        borrowerStatusLabel->setStyleSheet("QLabel { color: #9a6700; font-weight: 600; }");
        return;
    }

    LinkedList<std::string> *borrows = borrower->getUserActiveBorrows(userName);

    borrowerResultsList->clear();

    if (!borrows)
    {
        borrowerResultsList->addItem(QString::fromUtf8("ℹ️ No active borrows for this user."));
        updateBorrowerStatus("ℹ️ No active borrows found.");
        borrowerStatusLabel->setStyleSheet("QLabel { color: #0969da; font-weight: 600; }");
    }
    else
    {
        std::vector<std::string> borrowVec = borrows->toVector();
        if (borrowVec.empty())
        {
            borrowerResultsList->addItem(QString::fromUtf8("ℹ️ No active borrows for this user."));
            updateBorrowerStatus("ℹ️ No active borrows found.");
            borrowerStatusLabel->setStyleSheet("QLabel { color: #0969da; font-weight: 600; }");
        }
        else
        {
            for (const auto &record : borrowVec)
            {
                borrowerResultsList->addItem(QString::fromStdString("📚 " + record));
            }
            updateBorrowerStatus("✅ Found " + std::to_string(borrowVec.size()) + " active borrow(s).");
            borrowerStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
        }
    }
}

void LibraryGUI::handleViewBookBorrowers()
{
    std::string bookTitle = borrowerBookTitleInput->text().toStdString();

    if (bookTitle.empty())
    {
        updateBorrowerStatus("⚠️ Please enter a book title.");
        borrowerStatusLabel->setStyleSheet("QLabel { color: #9a6700; font-weight: 600; }");
        return;
    }

    LinkedList<std::string> *borrowers = borrower->getBookActiveBorrowers(bookTitle);

    borrowerResultsList->clear();

    if (!borrowers)
    {
        borrowerResultsList->addItem(QString::fromUtf8("ℹ️ No active borrowers for this book."));
        updateBorrowerStatus("ℹ️ No active borrowers found.");
        borrowerStatusLabel->setStyleSheet("QLabel { color: #0969da; font-weight: 600; }");
    }
    else
    {
        std::vector<std::string> borrowerVec = borrowers->toVector();
        if (borrowerVec.empty())
        {
            borrowerResultsList->addItem(QString::fromUtf8("ℹ️ No active borrowers for this book."));
            updateBorrowerStatus("ℹ️ No active borrowers found.");
            borrowerStatusLabel->setStyleSheet("QLabel { color: #0969da; font-weight: 600; }");
        }
        else
        {
            for (const auto &record : borrowerVec)
            {
                borrowerResultsList->addItem(QString::fromStdString("👤 " + record));
            }
            updateBorrowerStatus("✅ Found " + std::to_string(borrowerVec.size()) + " active borrower(s).");
            borrowerStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
        }
    }
}

void LibraryGUI::handleViewHistory()
{
    LinkedList<std::string> *history = borrower->getHistory();

    borrowerHistoryList->clear();

    if (!history)
    {
        borrowerHistoryList->addItem(QString::fromUtf8("ℹ️ No history available."));
        updateBorrowerStatus("ℹ️ No history found.");
        borrowerStatusLabel->setStyleSheet("QLabel { color: #0969da; font-weight: 600; }");
    }
    else
    {
        std::vector<std::string> historyVector = history->toVector();

        if (historyVector.empty())
        {
            borrowerHistoryList->addItem(QString::fromUtf8("ℹ️ No history available."));
            updateBorrowerStatus("ℹ️ No history found.");
            borrowerStatusLabel->setStyleSheet("QLabel { color: #0969da; font-weight: 600; }");
        }
        else
        {
            for (const auto &record : historyVector)
            {
                borrowerHistoryList->addItem(QString::fromStdString("📜 " + record));
            }
            updateBorrowerStatus("✅ Displaying " + std::to_string(historyVector.size()) + " history record(s).");
            borrowerStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
        }
    }
}

void LibraryGUI::handleLoadBorrowRecords()
{
    try
    {
        borrower->loadBorrowRecordsFromCSV("D:/HP/Projects/DSAE/Optimized-Library-Lookup-System/data/borrow_records.csv");
        updateBorrowerStatus("✅ Borrow records loaded successfully!");
        borrowerStatusLabel->setStyleSheet("QLabel { color: #1a7f37; font-weight: 600; }");
    }
    catch (const std::exception &e)
    {
        updateBorrowerStatus("❌ Error loading borrow records!");
        borrowerStatusLabel->setStyleSheet("QLabel { color: #cf222e; font-weight: 600; }");
    }
}

// Helper Methods
void LibraryGUI::refreshBookDisplay()
{
    bookDisplayList->clear();

    std::vector<std::pair<int, Book>> allBooks = bookManager->getAllBooks();

    if (allBooks.empty())
    {
        bookDisplayList->addItem(QString::fromUtf8("ℹ️ No books in the database."));
        return;
    }

    for (const auto &pair : allBooks)
    {
        const Book &book = pair.second;
        std::stringstream ss;
        ss << "📖 ID: " << book.getId()
           << " | Title: " << book.getTitle()
           << " | Author: " << book.getAuthor()
           << " | Year: " << book.getYear()
           << " | Publisher: " << book.getPublisher();
        bookDisplayList->addItem(QString::fromStdString(ss.str()));
    }
}

void LibraryGUI::updateStatusMessage(const std::string &message)
{
    bookStatusLabel->setText(QString::fromStdString(message));
}

void LibraryGUI::updateSearchStatus(const std::string &message)
{
    searchStatusLabel->setText(QString::fromStdString(message));
}

void LibraryGUI::updateBorrowerStatus(const std::string &message)
{
    borrowerStatusLabel->setText(QString::fromStdString(message));
}

void LibraryGUI::showAutoCompleteSuggestions(const std::string &prefix)
{
    // This method is kept for potential future use
    // Currently, auto-complete is handled in handleSearchTermChanged
}
