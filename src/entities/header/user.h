#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User
{
private:
    int id;
    string name;

public:
    User();
    User(int id, const string &name);

    int getId() const;
    string getName() const;

    void setName(const string &newName);
};

#endif