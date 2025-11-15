#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define C1 3
#define C2 4

string random_word_generator()
{
    string s = "";
    int n = rand() % 6 + 5;
    for (int i = 0; i < n; i++)
    {
        s += (char)(rand() % 26 + 97);
    }

    return s;
}

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
    while (table[index] != NULL && table[index] != Node::dummy && i < table_size * 5)
    {
        index = (hash_functions[hash_number](key, table_size) + i * auxHash(key, table_size)) % table_size;
        i++;
    }
    if (i == table_size * 5)
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
    while (table[index] != NULL && table[index] != Node::dummy && i < table_size * 5)
    {
        index = (hash_functions[hash_number](key, table_size) + C1 * i * auxHash(key, table_size) + C2 * i * i) % table_size;
        i++;
    }
    if (i == table_size * 5)
    {
        // cout << "cant insert " << key << endl;
        return 0;
    }
    table[index] = newnode;
    return 1;
}

ll (*collision_resolve[])(ll, string, Node *, Node **, ll, ll) = {seperate_chaining, double_hashing, custom_probing};

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
                while (table[index] != NULL && table[index]->key != key && i < table_size * 5)
                {
                    index = (hash_functions[hash_number](key, table_size) + i * auxHash(key, table_size)) % table_size;
                    i++;
                }
                if (i == table_size * 5)
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
                while (table[index] != NULL && table[index]->key != key && i < table_size * 5)
                {
                    index = (hash_functions[hash_number](key, table_size) + i * auxHash(key, table_size)) % table_size;
                    i++;
                }
                if (i == table_size * 5)
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
        if (index == 2)
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

int main()
{

    double store[3][2][3][2]; // size , hash_no , collision_method , collision_count/avg_probe
    srand(123);
    ll max_chain_length;
    cout << "Enter max chain length : " << endl;
    cin >> max_chain_length;
    // ll min_table_size;
    // cout << "Enter minimum table size : " << endl;
    // cin >> min_table_size;

    ll input[3] = {5000, 10000, 20000};
    string *words = new string[10000];
    map<string, ll> m;
    for (ll i = 0; i < 10000; i++)
    {
        string temp = random_word_generator();
        if (m.find(temp) == m.end())
        {
            m[temp] = 1;
            words[i] = temp;
        }
        else
        {
            i--;
        }
    }
    cout << endl;

    freopen("output.txt", "w", stdout);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            // cout << "size : " << input[i] << " hash_no : " << j << " collision_method : " << 0 << endl;
            cout << "\n   Table size : " << input[i] << endl;
            cout << "#### Seperate Chaining ####\n";
            cout << "# For Insertion\n";
            HashTable *openHash = new HashTable(input[i], j, 0); // size , hash_no , collision_method , collision_count/avg_probe
            for (int k = 0; k < 10000; k++)
            {
                openHash->insert(words[k]);
                if ((k + 1) % 100 == 0)
                {
                    ll chain_len = openHash->chain_length;
                    if (chain_len > max_chain_length)
                    {
                        cout << "\nBefore rehashing:" << endl;
                        cout << "Chain_length: " << openHash->chain_length << endl;
                        double load_factor = (double)openHash->curr_size / openHash->table_size;
                        cout << "Load factor: " << load_factor << endl;
                        double avg_prob_count = 0;
                        for (int i = 0; i < (k + 1) / 10; i++)
                        {
                            avg_prob_count += openHash->find(words[i]);
                        }
                        avg_prob_count /= (k + 1) / 10;
                        cout << "Avg_prob_count: " << avg_prob_count << endl;
                        cout << endl;

                        openHash->rehash(1);

                        load_factor = (double)openHash->curr_size / openHash->table_size;
                        cout << "After rehashing:" << endl;
                        cout << "Chain_length: " << openHash->chain_length << endl;
                        cout << "Load factor: " << load_factor << endl;
                        avg_prob_count = 0;
                        for (int i = 0; i < (k + 1) / 10; i++)
                        {
                            avg_prob_count += openHash->find(words[i]);
                        }
                        avg_prob_count /= (k + 1) / 10;
                        cout << "Avg_prob_count: " << avg_prob_count << endl;
                        cout << "---------------------------\n\n";
                    }
                }
            }
            // cout << openHash->curr_size << endl;
            store[i][j][0][0] = openHash->collisions;
            double avg_prob_count = 0;
            for (int k = 0; k < 1000; k++)
            {
                int random = rand() % 5000;
                avg_prob_count += openHash->find(words[random]);
            }
            avg_prob_count /= 1000;
            store[i][j][0][1] = avg_prob_count;
            // cout << "size : " << input[i] << " hash_no : " << j << endl;
            // cout << "collisions : " << openHash->collisions << " avg_probe : " << avg_prob_count << endl;

            /*for every 100 deletions*/
            cout << "# For Deletion\n";
            for (int k = 0; k < 10000; k++)
            {
                openHash->remove(words[k]);
                if ((k + 1) % 100 == 0)
                {
                    ll chain_len = openHash->chain_length;
                    if (chain_len < max_chain_length * 0.8)
                    {
                        cout << "\nBefore rehashing:" << endl;
                        cout << "Chain_length: " << openHash->chain_length << endl;
                        double load_factor = (double)openHash->curr_size / openHash->table_size;
                        cout << "Load factor: " << load_factor << endl;
                        double avg_prob_count = 0;
                        for (int i = 0; i < (k + 1) / 10; i++)
                        {
                            avg_prob_count += openHash->find(words[i]);
                        }
                        avg_prob_count /= (k + 1) / 10;
                        cout << "Avg_prob_count: " << avg_prob_count << endl;
                        cout << endl;

                        openHash->rehash(2);
                        cout << "After rehashing:" << endl;
                        cout << "Chain_length: " << openHash->chain_length << endl;
                        load_factor = (double)openHash->curr_size / openHash->table_size;
                        cout << "Load factor: " << load_factor << endl;
                        avg_prob_count = 0;
                        for (int i = 0; i < (k + 1) / 10; i++)
                        {
                            avg_prob_count += openHash->find(words[i]);
                        }
                        avg_prob_count /= (k + 1) / 10;
                        cout << "Avg_prob_count: " << avg_prob_count << endl;
                        cout << "---------------------------\n\n";
                    }
                }
            }

            delete openHash;
            cout << "---------------------------\n";
        }

        for (int j = 0; j < 2; j++)
        {
            for (int k = 1; k < 3; k++)
            {
                // cout << "size : " << input[i] << " hash_no : " << j << " collision_method : " << k << endl;
                HashTable *closedHash = new HashTable(input[i], j, k);
                for (int m = 0; m < 10000; m++)
                {
                    closedHash->insert(words[m]);

                    double load_factor = (double)closedHash->curr_size / closedHash->table_size;
                    if (load_factor > 0.7)
                    {
                        closedHash->rehash(1);
                    }
                }

                // cout << closedHash->curr_size << endl;
                // cout << "collisions :" << closedHash->collisions << endl;
                double avg_probe = 0;
                for (int i = 0; i < 1000; i++)
                {
                    long long int random_index = rand() % 5000;
                    string key = words[random_index];
                    avg_probe += closedHash->find(key);
                }
                // cout << "average probe : " << avg_probe / 1000 << endl;
                store[i][j][k][0] = closedHash->collisions;
                store[i][j][k][1] = avg_probe / 1000;

                delete closedHash;
            }
        }

        // cout << "---------------------------\n";
    }
    fclose(stdout);

    ofstream file("report.txt");
    file << " " << setw(87) << setfill('_') << "" << endl;
    file << setfill(' ');
    file << "| Hash       |     Collision       |     Hash Function 1     |     Hash Function 2     |" << endl;
    file << "| Table Size |  Resolution Method  |   Collisions |  Probes  |   Collisions | Probes   |" << endl;
    file << "|" << setw(87) << setfill('_') << "|" << endl;
    file << setfill(' ');

    for (int i = 0; i < 3; i++)
    {
        file << "|" << setw(10) << input[i] << setw(3) << "|";
        file << setw(19) << "Seperate chaining" << setw(3) << "|";
        file << setw(10) << store[i][0][0][0] << setw(5) << "|";
        file << setw(8) << store[i][0][0][1] << setw(3) << "|";
        file << setw(10) << store[i][1][0][0] << setw(5) << "|";
        file << setw(8) << store[i][1][0][1] << setw(3) << "|" << endl;
        file << "|" << setw(10) << input[i] << setw(3) << "|";
        file << setw(19) << "Double Hashing" << setw(3) << "|";
        file << setw(10) << store[i][0][1][0] << setw(5) << "|";
        file << setw(8) << store[i][0][1][1] << setw(3) << "|";
        file << setw(10) << store[i][1][1][0] << setw(5) << "|";
        file << setw(8) << store[i][1][1][1] << setw(3) << "|" << endl;
        file << "|" << setw(10) << input[i] << setw(3) << "|";
        file << setw(19) << "Custom Hashing" << setw(3) << "|";
        file << setw(10) << store[i][0][2][0] << setw(5) << "|";
        file << setw(8) << store[i][0][2][1] << setw(3) << "|";
        file << setw(10) << store[i][1][2][0] << setw(5) << "|";
        file << setw(8) << store[i][1][2][1] << setw(3) << "|" << endl;
        file << "|" << setw(87) << setfill(' ') << "|" << endl;
    }
    file << "|" << setw(87) << setfill('_') << "|" << endl;
    file.close();
    freopen("CON", "r", stdin);
    freopen("CON", "w", stdout);
    cout << "Report generated in report.txt" << endl;
    cout << "Success\n";
    return 0;
}