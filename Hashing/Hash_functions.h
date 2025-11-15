#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll hash1(string str, ll table_size)
{
    ll hash = 5381;
    for (const char &s : str)
    {
        hash = ((hash << 5) + hash) + static_cast<ll>(s);
    }
    return hash % table_size;
}
ll hash2(string str, ll table_size)
{
    ll hashVal = 0;
    for (int i = 0; i < str.length(); i++)
    {
        hashVal += (33 * hashVal) + str[i];
    }
    return hashVal % table_size;
}

ll auxHash(string str, ll table_size)
{
    const ll p = 31;
    ll q = 1;
    ll hash = 0;
    for (auto &c : str)
    {
        hash = (hash + (c - 'a' + 1) * q) % table_size;
        q = (q * p) % table_size;
    }
    return hash;
}
