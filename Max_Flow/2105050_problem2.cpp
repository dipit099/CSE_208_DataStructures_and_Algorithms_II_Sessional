#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ipair;

class Human
{
public:
    int height, age, isdivorced;
    Human() {}
    Human(int height, int age, int isdivorced)
    {
        this->height = height;
        this->age = age;
        this->isdivorced = isdivorced;
    }
};
int bfs(int vertex, int **capacity, vector<int> adj[], int source, int sink, vector<int> &parent)
{
    queue<ipair> q;
    // int flow = INT_MAX;
    for (int i = 0; i < vertex; i++)
        parent[i] = -1;
    parent[source] = -100;

    q.push({source, INT_MAX});
    while (q.size() != 0)
    {
        // cout << "as";
        ipair curr = q.front();
        q.pop();
        int curr_vertex = curr.first;
        int curr_flow = curr.second;
        for (int i = 0; i < adj[curr_vertex].size(); i++)
        {
            int next_vertex = adj[curr_vertex][i];
            if (parent[next_vertex] == -1 && capacity[curr_vertex][next_vertex] > 0) // parent -1 means jate ek vertex ek path e duibar choose na kora hy
            {
                parent[next_vertex] = curr_vertex;
                int new_flow = min(curr_flow, capacity[curr_vertex][next_vertex]);
                if (next_vertex == sink)
                {
                    // cout << "done" << endl;
                    return new_flow;
                }
                q.push({next_vertex, new_flow});
                // cout << "next_vertex: " << next_vertex << " new_flow: " << new_flow << endl;
            }
        }
    }
    return 0;
}

int maxflow(int vertex, int **capacity, vector<int> adj[], int source, int sink)
{
    int sinkflow = 0;
    vector<int> parent(vertex);
    while (true)
    {
        int new_flow = bfs(vertex, capacity, adj, source, sink, parent);
        if (new_flow == 0)
            break;
        sinkflow += new_flow;
        int curr = sink;
        while (curr != source)
        {
            int prev = parent[curr];
            capacity[prev][curr] -= new_flow;
            capacity[curr][prev] += new_flow;
            curr = prev;
        }
    }
    int maximum_flow = 0;
    int maximum_flow_vertex;
    for (int i = 0; i < vertex; i++)
    {
        // cout << i << ": ";
        for (int j = 0; j < vertex; j++)
        {
            // cout << capacity[i][j] << " ";
            if (capacity[i][j] > maximum_flow)
            {
                maximum_flow = capacity[i][j];
                maximum_flow_vertex = j + 1;
            }
        }

        // cout << endl;
    }
    // cout << maximum_flow_vertex << " " << maximum_flow << endl;
    return sinkflow;
}

int main()
{
    int man, woman;
    cin >> man >> woman;
    int vertex = man + woman + 2;

    int **capacity = new int *[vertex];
    for (int i = 0; i < vertex; i++)
        capacity[i] = new int[vertex];

    vector<int> adj[vertex];
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
            capacity[i][j] = 0;
    }

    Human matcharray[vertex];
    for (int i = 1; i < vertex - 1; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        matcharray[i] = Human(a, b, c);
        // a--;
        // b--;
        // capacity[a][b] = c;
        // adj[a].push_back(b);
        // adj[b].push_back(a);
    }
    int source = 0, sink = vertex - 1;
    for (int i = 1; i <= man; i++)
    {
        adj[source].push_back(i);
        adj[i].push_back(source);
        capacity[source][i] = 1;
    }
    for (int i = man + 1; i <= man + woman; i++)
    {
        adj[i].push_back(sink);
        adj[sink].push_back(i);
        capacity[i][sink] = 1;
    }

    for (int i = 1; i <= man; i++)
    {
        for (int j = man + 1; j <= man + woman; j++)
        {
            if (abs(matcharray[i].height - matcharray[j].height) <= 10 && abs(matcharray[i].age - matcharray[j].age) <= 5 && matcharray[i].isdivorced == matcharray[j].isdivorced)
            {
                adj[i].push_back(j);
                adj[j].push_back(i);
                capacity[i][j] = 1;
            }
        }
    }

    cout << maxflow(vertex, capacity, adj, source, sink) << endl;
}