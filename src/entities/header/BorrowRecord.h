#ifndef BORROW_RECORD_H
#define BORROW_RECORD_H
#include <string>
using namespace std;

class BorrowRecord
{
private:
    int userId;
    int bookId;
    string dateBorrowed;

public:
    BorrowRecord();
    BorrowRecord(int userId, int bookId, const string &dateBorrowed);

    int getUserId() const;
    int getBookId() const;
    string getDateBorrowed() const;
};

#endif