#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
using namespace std;

class TrieNode
{
public:
    TrieNode *children[26];
    bool isEnd;

    TrieNode();
};

class Trie
{
private:
    TrieNode *root;

public:
    Trie();
    void insert(const string &word);
    vector<string> getAutoComplete(const string &prefix);

private:
    void collect(TrieNode *node, string prefix, vector<string> &results);
    TrieNode *searchPrefix(const string &prefix);
};

#endif
