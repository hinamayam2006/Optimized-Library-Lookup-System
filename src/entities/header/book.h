#ifndef BOOK_H
#define BOOK_H
#include <string>
using namespace std;

class Book
{
private:
    int id;
    string title;
    string author;
    int year;
    string publisher;

public:
    Book();
    Book(int id, const string &title, const string &author, int year, const string &publisher = "Unknown Publisher");

    // Getters
    int getId() const;
    string getTitle() const;
    string getAuthor() const;
    int getYear() const;
    string getPublisher() const;

    // Setters
    void setTitle(const string &newTitle);
    void setAuthor(const string &newAuthor);
    void setYear(int newYear);
    void setPublisher(const string &newPublisher);
};

#endif