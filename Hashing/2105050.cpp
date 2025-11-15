#include "Hashtable.h"
#include <bits/stdc++.h>
using namespace std;

#define MOD 8000

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
                int random = rand() % MOD;
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

                    // double load_factor = (double)closedHash->curr_size / closedHash->table_size;
                    // if (load_factor >=2)
                    // {
                    //     closedHash->rehash(1);
                    // }
                }

                // cout << closedHash->curr_size << endl;
                // cout << "collisions :" << closedHash->collisions << endl;
                double avg_probe = 0;
                for (int i = 0; i < 1000; i++)
                {
                    long long int random_index = rand() % MOD;
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

    file << " C1: " << C1 << " C2: " << C2 << endl;
    file << " Max Chain Length :" << max_chain_length << "" << endl;
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