#include "BorrowRecord.h"

BorrowRecord::BorrowRecord() : userId(0), bookId(0), dateBorrowed("") {}

BorrowRecord::BorrowRecord(int userId, int bookId, const string &dateBorrowed)
    : userId(userId), bookId(bookId), dateBorrowed(dateBorrowed) {}

int BorrowRecord::getUserId() const { return userId; }
int BorrowRecord::getBookId() const { return bookId; }
string BorrowRecord::getDateBorrowed() const { return dateBorrowed; }