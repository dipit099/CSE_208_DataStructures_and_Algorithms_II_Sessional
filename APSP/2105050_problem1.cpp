#include <bits/stdc++.h>
using namespace std;
int main()
{
    int vertex, edges;
    cin >> vertex >> edges;
    vector<pair<int, int>> adj[vertex];
    for (int i = 0; i < edges; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    int limit;
    cin >> limit;
    long long int dismatrix[vertex][vertex];
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            if (i == j)
                dismatrix[i][j] = 0;
            else
                dismatrix[i][j] = INT_MAX;
        }
    }
    // for (int i = 0; i < vertex; i++)
    // {
    //     for (int j = 0; j < vertex; j++)
    //     {
    //         cout << dismatrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < adj[i].size(); j++)
        {
            int vertex = adj[i][j].first;
            int weight = adj[i][j].second;
            if (weight < dismatrix[i][vertex])
            {
                dismatrix[i][vertex] = weight;
                dismatrix[vertex][i] = weight;
            }
        }
    }

    vector<int> count(vertex, 0);
    int mini = INT_MAX;

    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            for (int k = 0; k < vertex; k++)
            {
                dismatrix[j][k] = min(dismatrix[j][k], dismatrix[j][i] + dismatrix[i][k]);
                if (i == vertex - 1)
                {
                    if (dismatrix[j][k] <= limit)
                        count[j]++;
                }
            }
            if (i == vertex - 1)
                mini = min(mini, count[j]);
        }
        // for (int i = 0; i < vertex; i++)
        // {
        //     for (int j = 0; j < vertex; j++)
        //     {
        //         cout << dismatrix[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        // cout << endl;
    }
    for (int i = 0; i < vertex; i++)
    {
        if (count[i] == mini)
            cout << i + 1 << ' ';
    }
}