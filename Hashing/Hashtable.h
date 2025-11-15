#include "Collision_resolve.h"
#include <bits/stdc++.h>
using namespace std;

ll (*collision_resolve[])(ll, string, Node *, Node **, ll, ll) = {seperate_chaining, double_hashing, custom_probing};

bool isprime(long long int n)
{
    if (n == 1)
    {
        return false;
    }
    for (long long int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}
long long int findnxtprime(long long int n)
{
    while (true)
    {
        if (isprime(n))
        {
            return n;
        }
        n++;
    }
}
class HashTable
{
public:
    ll table_size, initial_size, curr_size, collision_method, hash_number;
    Node **table;
    ll collisions, key_value, chain_length;
    HashTable(ll table_size, ll hash_number, ll collision_method)
    {
        this->initial_size = table_size;
        this->table_size = findnxtprime(table_size);
        this->table = new Node *[this->table_size];
        for (ll i = 0; i < this->table_size; i++)
        {
            table[i] = NULL;
        }
        this->hash_number = hash_number;
        this->collision_method = collision_method;
        this->collisions = 0;
        this->key_value = 1;
        this->chain_length = 0;
        this->curr_size = 0;
    }

    void insert(string key)
    {
        if (collision_method == 0)
        {
            ll index = hash_functions[hash_number](key, table_size);
            Node *newnode = new Node(key, key_value);
            if (table[index] == NULL)
            {
                table[index] = newnode;
            }
            else
            {
                collisions++;
                ll temp = collision_resolve[collision_method](index, key, newnode, table, table_size, hash_number);
                chain_length = max(chain_length, temp);
            }
            curr_size++;
            key_value++;
        }
        else
        {
            if (curr_size == table_size)
            {
                // cout << "table full" << endl;
                collisions++;
                return;
            }
            ll index = hash_functions[hash_number](key, table_size);
            Node *newnode = new Node(key, key_value);
            if (table[index] == NULL)
            {
                table[index] = newnode;
                curr_size++;
                key_value++;
            }
            else
            {
                collisions++;
                int temp = collision_resolve[collision_method](index, key, newnode, table, table_size, hash_number);
                if (temp >= 1)
                {
                    curr_size++;
                    key_value++;
                    return;
                }
            }
        }
        return;
    }

    ll find(string key)
    {
        if (collision_method == 0)
        {
            ll index = hash_functions[hash_number](key, table_size);
            if (table[index] == NULL)
            {
                return 1;
            }
            else
            {
                ll itr = 1;
                Node *temp = table[index];
                while (temp != NULL && temp->key != key)
                {
                    temp = temp->next;
                    itr++;
                }
                return itr;
            }
        }
        else
        {
            ll index = hash_functions[hash_number](key, table_size);
            if (table[index] == NULL)
            {
                return 1;
            }
            else
            {
                ll i = 0;
                while (table[index] != NULL && table[index]->key != key && i < table_size)
                {
                    if (collision_method == 1)
                    {
                        index = (hash_functions[hash_number](key, table_size) + i * auxHash(key, table_size)) % table_size;
                    }
                    else
                    {
                        index = (hash_functions[hash_number](key, table_size) + C1 * i * auxHash(key, table_size) + C2 * i * i) % table_size;
                    }
                    i++;
                }
                if (i == table_size)
                {
                    return 0;
                }
                else
                {
                    return i + 1;
                }
            }
        }
    }

    void remove(string key)
    {
        if (collision_method == 0)
        {
            ll index = hash_functions[hash_number](key, table_size);
            if (table[index] == NULL)
            {
                return;
            }
            else
            {
                Node *temp = table[index];
                if (temp->key == key)
                {
                    table[index] = temp->next;
                    delete temp;
                    return;
                }
                while (temp->next != NULL && temp->next->key != key)
                {
                    temp = temp->next;
                }
                if (temp->next == NULL)
                {
                    return;
                }
                Node *temp2 = temp->next;
                temp->next = temp2->next;
                delete temp2;
                return;
            }
        }
        else
        {
            ll index = hash_functions[hash_number](key, table_size);
            if (table[index] == NULL)
            {
                return;
            }
            else
            {
                ll i = 0;
                while (table[index] != NULL && table[index]->key != key && i < table_size)
                {
                    if (collision_method == 1)
                        index = (hash_functions[hash_number](key, table_size) + i * auxHash(key, table_size)) % table_size;
                    else
                        index = (hash_functions[hash_number](key, table_size) + C1 * i * auxHash(key, table_size) + C2 * i * i) % table_size;
                    i++;
                }
                if (i == table_size)
                {
                    return;
                }
                else
                {
                    delete table[index];
                    table[index] = Node::dummy;
                    return;
                }
            }
        }
    }

    void rehash(int index)
    {
        if (index == 1)
        {
            curr_size = 0;
            key_value = 1;
            chain_length = 0;
            ll old_table_size = table_size;
            Node **old_table = table;
            table_size = findnxtprime(table_size * 2);
            table = new Node *[table_size];
            for (ll i = 0; i < table_size; i++)
            {
                table[i] = NULL;
            }

            for (ll i = 0; i < old_table_size; i++)
            {
                if (old_table[i] != NULL)
                {
                    Node *temp = old_table[i];
                    while (temp != NULL)
                    {
                        insert(temp->key);
                        temp = temp->next;
                    }
                }
            }
            for (ll i = 0; i < old_table_size; i++)
            {
                if (old_table[i] != NULL)
                {
                    delete old_table[i];
                }
            }
            delete[] old_table;
        }
        else if (index == 2)
        {
            curr_size = 0;
            key_value = 1;
            chain_length = 0;
            ll old_table_size = table_size;
            Node **old_table = table;
            ll temp = findnxtprime(table_size / 2);
            if (temp < initial_size)
            {
                return;
            }
            else
            {
                table_size = temp;
            }

            table = new Node *[table_size];
            for (ll i = 0; i < table_size; i++)
            {
                table[i] = NULL;
            }

            for (ll i = 0; i < old_table_size; i++)
            {
                if (old_table[i] != NULL)
                {
                    Node *temp = old_table[i];
                    while (temp != NULL)
                    {
                        insert(temp->key);
                        temp = temp->next;
                    }
                }
            }
            for (ll i = 0; i < old_table_size; i++)
            {
                if (old_table[i] != NULL)
                {
                    delete old_table[i];
                }
            }
            delete[] old_table;
        }
    }
};
