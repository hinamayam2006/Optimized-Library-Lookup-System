#ifndef LINKED_LIST_H
#define LINKED_LIST_H

using namespace std;

template <typename T>
struct Node
{
    T data;
    Node *next;

    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class LinkedList
{
private:
    Node<T> *head;

public:
    LinkedList();
    ~LinkedList();

    void insertAtEnd(const T &data);
    bool remove(const T &data);
    bool search(const T &data);
    void clear();
};

#endif
