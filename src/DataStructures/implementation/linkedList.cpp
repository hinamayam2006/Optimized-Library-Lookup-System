#include "../header/linkedList.h"
#include <string>
using namespace std;

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
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
}

template class LinkedList<int>;
template class LinkedList<string>;
