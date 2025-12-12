#include "../header/linkedList.h"
#include <string>
#include <vector>
using namespace std;

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList &other) : head(nullptr)
{
    Node<T> *temp = other.head;
    while (temp)
    {
        insertAtEnd(temp->data);
        temp = temp->next;
    }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList &other)
{
    if (this == &other)
        return *this;
    clear();
    head = nullptr;
    Node<T> *temp = other.head;
    while (temp)
    {
        insertAtEnd(temp->data);
        temp = temp->next;
    }
    return *this;
}

template <typename T>
void LinkedList<T>::insertAtEnd(const T &data)
{
    Node<T> *node = new Node<T>(data);

    if (!head)
    {
        head = node;
        return;
    }

    Node<T> *temp = head;
    while (temp->next)
        temp = temp->next;

    temp->next = node;
}

template <typename T>
bool LinkedList<T>::remove(const T &data)
{
    Node<T> *temp = head;
    Node<T> *prev = nullptr;

    while (temp)
    {
        if (temp->data == data)
        {
            if (prev)
                prev->next = temp->next;
            else
                head = temp->next;

            delete temp;
            return true;
        }
        prev = temp;
        temp = temp->next;
    }
    return false;
}

template <typename T>
bool LinkedList<T>::search(const T &data)
{
    Node<T> *temp = head;
    while (temp)
    {
        if (temp->data == data)
            return true;
        temp = temp->next;
    }
    return false;
}

template <typename T>
void LinkedList<T>::clear()
{
    Node<T> *temp = head;
    while (temp)
    {
        Node<T> *next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
}

template <typename T>
std::vector<T> LinkedList<T>::toVector() const
{
    std::vector<T> out;
    Node<T> *temp = head;
    while (temp)
    {
        out.push_back(temp->data);
        temp = temp->next;
    }
    return out;
}

template class LinkedList<int>;
template class LinkedList<string>;
