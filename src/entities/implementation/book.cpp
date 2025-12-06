#include "Book.h"

Book::Book() : id(0), year(0), title(""), author(""), publisher("") {}

Book::Book(int id, const string &title, const string &author, int year, const string &publisher)
    : id(id), title(title), author(author), year(year), publisher(publisher) {}

int Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }
string Book::getPublisher() const { return publisher; }

void Book::setTitle(const string &newTitle) { title = newTitle; }
void Book::setAuthor(const string &newAuthor) { author = newAuthor; }
void Book::setYear(int newYear) { year = newYear; }
void Book::setPublisher(const string &newPublisher) { publisher = newPublisher; }