#include "Hash_functions.h"
#include <bits/stdc++.h>
using namespace std;
#define C1 5113
#define C2 10159
class Node
{
public:
    string key;
    ll value;
    Node *next;
    static Node *dummy;
    Node(string key, ll value)
    {
        this->key = key;
        this->value = INT_MAX;
        next = NULL;
    }
};

Node *Node::dummy = new Node("", -1);

ll (*hash_functions[])(string, ll) = {hash1, hash2, auxHash};

ll seperate_chaining(ll index, string key, Node *newnode, Node **table, ll table_size, ll hash_number)
{
    ll chain_length = 1;
    Node *temp = table[index];
    while (temp->next != NULL)
    {
        temp = temp->next;
        chain_length++;
    }
    temp->next = newnode;
    return chain_length;
}

ll double_hashing(ll index, string key, Node *newnode, Node **table, ll table_size, ll hash_number)
{
    ll i = 0;
    int temp = index;
    while (table[index] != NULL && table[index] != Node::dummy && i < table_size)
    {
        index = (hash_functions[hash_number](key, table_size) + i * auxHash(key, table_size)) % table_size;
        i++;
    }
    if (i == table_size)
    {
        // cout << "cant insert" << key << endl;
        return 0;
    }
    table[index] = newnode;
    return 1;
}

ll custom_probing(ll index, string key, Node *newnode, Node **table, ll table_size, ll hash_number)
{
    ll i = 0;
    while (table[index] != NULL && table[index] != Node::dummy && i < table_size)
    {
        index = (hash_functions[hash_number](key, table_size) + C1 * i * auxHash(key, table_size) + C2 * i * i) % table_size;
        i++;
    }
    if (i == table_size)
    {
        // cout << "cant insert " << key << endl;
        return 0;
    }
    table[index] = newnode;
    return 1;
}
