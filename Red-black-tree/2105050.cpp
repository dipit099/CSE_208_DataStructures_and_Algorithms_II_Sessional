/*Red black tree*/
#include "Red_black_tree.h"
#include <bits/stdc++.h>
using namespace std;

class Map
{
public:
    Red_black_tree rbt;
    Map()
    {
        rbt = Red_black_tree();
    }
    void insert(int key, string data)
    {
        rbt.insert(key, data);
    }
    bool erase(int key)
    {
        return rbt.erase(key);
    }
    bool clear()
    {
        return rbt.clear();
    }
    bool empty()
    {
        return rbt.empty();
    }
    int size()
    {
        return rbt.length();
    }
    bool find(int key)
    {
        return rbt.find(key);
    }
    void iteration()
    {
        rbt.iteration(rbt.root);
    }
    void inorder()
    {
        rbt.inorder(rbt.root);
    }
};

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    Map mymap;
    while (1)
    {
        string s;
        cin >> s;

        if (s == "Clr")
        {
            if (mymap.clear())
            {
                cout << "successful" << endl;
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
        else if (s == "Em")
        {
            if (mymap.empty())
            {
                cout << "yes" << endl;
            }
            else
            {
                cout << "no" << endl;
            }
        }
        else if (s == "I")
        {
            int key;
            string data;
            cin >> key >> data;
            // cout << "Inserting " << key << "_" << data << endl;
            mymap.insert(key, data);
            mymap.iteration();
            cout << endl;
        }
        else if (s == "E")
        {
            int key;
            cin >> key;
            if (mymap.erase(key))
            {
                mymap.iteration();
            }
            else
            {
                cout << key << " not found";
            }
            cout << endl;
        }
        else if (s == "F")
        {
            int key;
            cin >> key;
            if (mymap.find(key))
            {
                cout << key << (" found") << endl;
            }
            else
            {
                cout << key << " not found" << endl;
            }
        }
        else if (s == "S")
        {
            cout << mymap.size() << endl;
        }
        else if (s == "Itr")
        {
            mymap.inorder();
            cout << endl;
        }

        else
        {
            cout << "Invalid command" << endl;
            return 0;
        }
        // cout << endl;
    }
}