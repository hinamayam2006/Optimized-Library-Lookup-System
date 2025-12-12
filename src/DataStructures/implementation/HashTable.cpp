#include "../header/HashTable.h"
#include <functional>

// HashNode constructor
template <typename K, typename V>
HashNode<K, V>::HashNode(K k, V v) : key(k), value(v), next(nullptr) {}

// HashTable implementations
template <typename K, typename V>
HashTable<K, V>::HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = nullptr;
}

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode<K, V> *entry = table[i];
        while (entry)
        {
            HashNode<K, V> *prev = entry;
            entry = entry->next;
            delete prev;
        }
    }
}

template <typename K, typename V>
int HashTable<K, V>::hashFunction(const K &key)
{
    std::hash<K> hasher;
    return hasher(key) % TABLE_SIZE;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const K &key, const V &value)
{
    int index = hashFunction(key);
    HashNode<K, V> *newNode = new HashNode<K, V>(key, value);
    newNode->next = table[index];
    table[index] = newNode;
    return true;
}

template <typename K, typename V>
V *HashTable<K, V>::search(const K &key)
{
    int index = hashFunction(key);
    HashNode<K, V> *entry = table[index];
    while (entry)
    {
        if (entry->key == key)
            return &entry->value;
        entry = entry->next;
    }
    return nullptr;
}

template <typename K, typename V>
bool HashTable<K, V>::update(const K &key, const V &newValue)
{
    V *val = search(key);
    if (!val)
        return false;
    *val = newValue;
    return true;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K &key)
{
    int index = hashFunction(key);
    HashNode<K, V> *entry = table[index];
    HashNode<K, V> *prev = nullptr;

    while (entry)
    {
        if (entry->key == key)
        {
            if (prev)
                prev->next = entry->next;
            else
                table[index] = entry->next;

            delete entry;
            return true;
        }
        prev = entry;
        entry = entry->next;
    }
    return false;
}

template <typename K, typename V>
vector<pair<K, V>> HashTable<K, V>::getAllEntries() const
{
    vector<pair<K, V>> entries;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode<K, V> *entry = table[i];
        while (entry)
        {
            entries.push_back(make_pair(entry->key, entry->value));
            entry = entry->next;
        }
    }
    return entries;
}

// -----------------------
// Explicit template instantiation
// -----------------------
#include "../entities/header/book.h"
#include "../header/linkedList.h"

template class HashTable<int, Book>;                       // for your BookManager usage
template class HashTable<string, string>;                  // if you need string/string hash table
template class HashTable<int, LinkedList<std::string>>;    // for Borrower module
template class HashTable<string, LinkedList<std::string>>; // name/title based Borrower
