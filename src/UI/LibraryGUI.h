#ifndef LIBRARYGUI_H
#define LIBRARYGUI_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QLabel>
#include <string>
#include <vector>

#include "BookManager.h"
#include "SearchAndSort.h"
#include "Borrower.h"

class LibraryGUI : public QMainWindow
{
    Q_OBJECT

private:
    BookManager *bookManager;
    SearchAndSort *searchAndSort;
    Borrower *borrower;

    // Main Widget and Layout
    QWidget *centralWidget;
    QTabWidget *tabWidget;

    // Book Management Tab Components
    QWidget *bookManagementTab;
    QLineEdit *bookIdInput;
    QLineEdit *bookTitleInput;
    QLineEdit *bookAuthorInput;
    QLineEdit *bookYearInput;
    QLineEdit *bookPublisherInput;
    QPushButton *addBookBtn;
    QPushButton *updateBookBtn;
    QPushButton *deleteBookBtn;
    QPushButton *searchBookBtn;
    QPushButton *loadBooksBtn;
    QPushButton *saveBooksBtn;
    QPushButton *displayAllBooksBtn;
    QListWidget *bookDisplayList;
    QLabel *bookStatusLabel;

    // Search & Sort Tab Components
    QWidget *searchSortTab;
    QLineEdit *searchTermInput;
    QPushButton *searchByTitleBtn;
    QPushButton *sortByTitleBtn;
    QPushButton *sortByYearBtn;
    QPushButton *sortByAuthorBtn;
    QPushButton *loadAutoCompleteBtn;
    QListWidget *searchResultsList;
    QListWidget *suggestionsList;
    QLabel *searchStatusLabel;

    // Borrower Management Tab Components
    QWidget *borrowerTab;
    QLineEdit *borrowerUserNameInput;
    QLineEdit *borrowerBookTitleInput;
    QLineEdit *borrowerDateInput;
    QPushButton *borrowBookBtn;
    QPushButton *returnBookBtn;
    QPushButton *viewUserBorrowsBtn;
    QPushButton *viewBookBorrowersBtn;
    QPushButton *viewHistoryBtn;
    QPushButton *loadBorrowRecordsBtn;
    QListWidget *borrowerResultsList;
    QListWidget *borrowerHistoryList;
    QLabel *borrowerStatusLabel;

    // Helper methods
    void setupUI();
    QWidget *createBookManagementTab();
    QWidget *createSearchSortTab();
    QWidget *createBorrowerTab();
    void refreshBookDisplay();
    void updateStatusMessage(const std::string &message);
    void updateSearchStatus(const std::string &message);
    void showAutoCompleteSuggestions(const std::string &prefix);

private slots:
    void handleAddBook();
    void handleUpdateBook();
    void handleDeleteBook();
    void handleSearchBook();
    void handleLoadBooks();
    void handleSaveBooks();
    void handleDisplayAllBooks();

    void handleSearchByTitle();
    void handleSortByTitle();
    void handleSortByYear();
    void handleSortByAuthor();
    void handleLoadAutoComplete();
    void handleSearchTermChanged();
    void handleSuggestionClick();

    void handleBorrowBook();
    void handleReturnBook();
    void handleViewUserBorrows();
    void handleViewBookBorrowers();
    void handleViewHistory();
    void handleLoadBorrowRecords();
    void updateBorrowerStatus(const std::string &message);

public:
    explicit LibraryGUI(QWidget *parent = nullptr);
    ~LibraryGUI();
};

#endif
