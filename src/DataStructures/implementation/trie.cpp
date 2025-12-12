#include "../header/trie.h"

TrieNode::TrieNode()
{
    isEnd = false;
    for (int i = 0; i < 128; i++)
        children[i] = nullptr;
}

Trie::Trie()
{
    root = new TrieNode();
}

void Trie::insert(const string &word)
{
    TrieNode *node = root;
    for (char c : word)
    {
        int idx = (unsigned char)tolower(c);
        if (idx < 0 || idx >= 128)
            continue;
        if (!node->children[idx])
            node->children[idx] = new TrieNode();
        node = node->children[idx];
    }
    node->isEnd = true;
}

TrieNode *Trie::searchPrefix(const string &prefix)
{
    TrieNode *node = root;
    for (char c : prefix)
    {
        int idx = (unsigned char)tolower(c);
        if (idx < 0 || idx >= 128)
            return nullptr;
        if (!node->children[idx])
            return nullptr;
        node = node->children[idx];
    }
    return node;
}

void Trie::collect(TrieNode *node, string prefix, vector<string> &results)
{
    if (!node)
        return;

    if (node->isEnd)
        results.push_back(prefix);

    for (int i = 0; i < 128; i++)
        if (node->children[i])
            collect(node->children[i], prefix + char(i), results);
}

vector<string> Trie::getAutoComplete(const string &prefix)
{
    vector<string> results;
    TrieNode *start = searchPrefix(prefix);

    if (!start)
        return results;

    collect(start, prefix, results);
    return results;
}
