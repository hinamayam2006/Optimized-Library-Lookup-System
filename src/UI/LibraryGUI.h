#ifndef LIBRARYGUI_H
#define LIBRARYGUI_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Int_Input.H>
#include <string>
#include <vector>

#include "BookManager.h"
#include "SearchAndSort.h"

class LibraryGUI : public Fl_Window
{
private:
    BookManager *bookManager;
    SearchAndSort *searchAndSort;

    // Book Management Tab Components
    Fl_Group *bookManagementTab;
    Fl_Int_Input *bookIdInput;
    Fl_Input *bookTitleInput;
    Fl_Input *bookAuthorInput;
    Fl_Int_Input *bookYearInput;
    Fl_Input *bookPublisherInput;
    Fl_Button *addBookBtn;
    Fl_Button *updateBookBtn;
    Fl_Button *deleteBookBtn;
    Fl_Button *searchBookBtn;
    Fl_Button *loadBooksBtn;
    Fl_Button *saveBooksBtn;
    Fl_Button *displayAllBooksBtn;
    Fl_Browser *bookDisplayBrowser;
    Fl_Output *bookStatusOutput;

    // Search & Sort Tab Components
    Fl_Group *searchSortTab;
    Fl_Input *searchTermInput;
    Fl_Button *searchByTitleBtn;
    Fl_Button *sortByTitleBtn;
    Fl_Button *sortByYearBtn;
    Fl_Button *sortByAuthorBtn;
    Fl_Button *loadAutoCompleteBtn;
    Fl_Browser *searchResultsBrowser;
    Fl_Browser *suggestionsBrowser;
    Fl_Output *searchStatusOutput;

    // Helper methods
    void refreshBookDisplay();
    void updateStatusMessage(const std::string &message);
    void updateSearchStatus(const std::string &message);
    void showAutoCompleteSuggestions(const std::string &prefix);
    static void searchTermChangedCallback(Fl_Widget *w, void *data);
    static void suggestionClickedCallback(Fl_Widget *w, void *data);
    void handleSuggestionClick();

public:
    LibraryGUI(int w, int h, const char *title);
    ~LibraryGUI();

    // Callback methods (static to work with FLTK)
    static void addBookCallback(Fl_Widget *w, void *data);
    static void updateBookCallback(Fl_Widget *w, void *data);
    static void deleteBookCallback(Fl_Widget *w, void *data);
    static void searchBookCallback(Fl_Widget *w, void *data);
    static void loadBooksCallback(Fl_Widget *w, void *data);
    static void saveBooksCallback(Fl_Widget *w, void *data);
    static void displayAllBooksCallback(Fl_Widget *w, void *data);

    static void searchByTitleCallback(Fl_Widget *w, void *data);
    static void sortByTitleCallback(Fl_Widget *w, void *data);
    static void sortByYearCallback(Fl_Widget *w, void *data);
    static void sortByAuthorCallback(Fl_Widget *w, void *data);
    static void loadAutoCompleteCallback(Fl_Widget *w, void *data);

    // Instance methods that callbacks call
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
};

#endif
