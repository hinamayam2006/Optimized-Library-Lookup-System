#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
using namespace std;

template <typename K, typename V>
struct HashNode
{
    K key;
    V value;
    HashNode *next;

    HashNode(K k, V v) : key(k), value(v), next(nullptr) {}
};

template <typename K, typename V>
class HashTable
{
private:
    static const int TABLE_SIZE = 1000;
    HashNode<K, V> *table[TABLE_SIZE];

    int hashFunction(const K &key);

public:
    HashTable();
    ~HashTable();

    bool insert(const K &key, const V &value);
    V *search(const K &key);
    bool update(const K &key, const V &newValue);
    bool remove(const K &key);
};

#endif
