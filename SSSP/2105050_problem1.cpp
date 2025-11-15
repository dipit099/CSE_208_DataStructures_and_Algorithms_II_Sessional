#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ipair;

// class Node
// {
// public:
//     int ver, oil, cost;
//     Node() {}
//     Node(int ver, int oil, int cost)
//     {
//         this->ver = ver;
//         this->oil = oil;
//         this->cost = cost;
//     }
// };
int shortestpath(int src, int dest, int aver, int vertex, vector<pair<ipair, int>> adj[], int capacity);

int main()
{
    int vertex, edge, capacity;
    cin >> vertex >> edge >> capacity;
    vector<pair<ipair, int>> adj[vertex * (capacity + 1)]; // vertex, weight, cost
    int cc = 0;
    for (int i = 0; i < vertex; i++)
    {
        int percost;
        cin >> percost;

        for (int j = 0; j <= capacity; j++)
        {
            adj[cc].push_back(make_pair(make_pair(i, j), 0));
            for (int m = 0; m <= capacity; m++)
            {
                if (m != j)
                {
                    adj[cc].push_back(make_pair(make_pair(i, m), abs(m - j) * percost));
                }
            }
            cc++;
        }
    }

    for (int i = 0; i < edge; i++)
    {
        int start, end, weight;
        cin >> start >> end >> weight;
        start--;
        end--;
        // do for start
        int sindex = start + capacity * start, eindex = end + capacity * end;

        // iterate
        int k = 0;
        while (1)
        {
            if ((eindex + weight + k) < cc && (eindex + weight + k) >= 0 && adj[eindex + weight + k][0].first.first == end)
            {
                adj[eindex + weight + k].push_back(make_pair(adj[sindex + k][0].first, 0));
                k++;
            }
            else
            {
                break;
            }
        }
        k = 0;
        // do reverse too
        while (1)
        {
            if (sindex + weight + k < cc && sindex + weight + k >= 0 && adj[sindex + weight + k][0].first.first == start)
            {
                adj[sindex + weight + k].push_back(make_pair(adj[eindex + k][0].first, 0));
                k++;
            }
            else
            {
                break;
            }
        }
    }
    // print adj list

    // for (int i = 0; i < cc; i++)
    // {
    //     cout << i << "-> (";
    //     for (int j = 0; j < adj[i].size(); j++)
    //     {
    //         cout << adj[i][j].first.first << " " << adj[i][j].first.second << " " << adj[i][j].second << "),( ";
    //     }
    //     cout << endl;
    // }

    int src, dest;
    cin >> src >> dest;
    src--;
    dest--;
    int ans = shortestpath(src, dest, vertex, cc, adj, capacity);
    if (ans != INT_MAX)
        cout << ans;
    else
        cout << "impossible";
}
int shortestpath(int src, int dest, int aver, int vertex, vector<pair<ipair, int>> adj[], int capacity)
{
    priority_queue<pair<ipair, int>, vector<pair<ipair, int>>, greater<pair<ipair, int>>> pq; // cost, vertex, left oil  //min queue
    vector<int> dist(vertex, INT_MAX);
    vector<int> ans(aver, INT_MAX);
    pq.push(make_pair(make_pair(0, src), 0)); // cost, src, oil
    dist[src + capacity * src] = 0;

    while (pq.size() != 0)
    {
        int u = pq.top().first.second; // vertex
        int sindex = u;
        int oil = pq.top().second;
        u = u + capacity * u + oil; // index number

        // cout << sindex << " " << oil << " " << dist[u] << endl;
        pq.pop();

        for (int i = 1; i < adj[u].size(); i++)
        {
            int ver = adj[u][i].first.first + capacity * adj[u][i].first.first + adj[u][i].first.second;

            if (dist[u] + adj[u][i].second < dist[ver])
            {
                dist[ver] = dist[u] + adj[u][i].second;
                pq.push(make_pair(make_pair(dist[ver + i], adj[u][i].first.first), adj[u][i].first.second));
                // cout << sindex << ' ' << oil << " ver " << adj[u][i].first.first << " " << adj[u][i].first.second << ' ' << dist[u] << ' ' << adj[u][i].second << ' ' << dist[ver] << endl;
                ans[adj[u][i].first.first] = min(ans[adj[u][i].first.first], dist[ver]);
            }
            // cout << "ver " << adj[u][i].first.first << " " << adj[u][i].first.second << ' ' << dist[ver + i] << endl;
        }
    }
    return ans[dest];
}