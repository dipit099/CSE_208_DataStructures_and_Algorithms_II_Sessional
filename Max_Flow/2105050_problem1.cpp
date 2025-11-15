#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ipair;

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

class Output
{
public:
    int maximum_flow_vertex, maximum_flow, sinkflow;
    int **capacity;
    Output(int maximum_flow_vertex, int maximum_flow, int **capacity, int sinkflow)
    {
        this->maximum_flow_vertex = maximum_flow_vertex;
        this->maximum_flow = maximum_flow;
        this->capacity = capacity;
        this->sinkflow = sinkflow;
    }
};

Output maxflow(int vertex, int **capacity, vector<int> adj[], int source, int sink)
{
    int sinkflow = 0;
    vector<int> parent(vertex);
    while (true)
    {
        int new_flow = bfs(vertex, capacity, adj, source, sink, parent);
        if (new_flow == 0) // if zero then means no augmented path found
            break;
        sinkflow += new_flow; // sinkflow is the total flow from source to sink
        int curr = sink;
        while (curr != source) // bfs chalaia parent array set kre feli everytime..thus we know the path that we found by bfs
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
    // return sinkflow;
    Output output(maximum_flow_vertex, maximum_flow, capacity, sinkflow); // return as object
    return output;
}

void dfs(int **capacity, int curr, vector<int> adj[], vector<int> &visited)
{
    for (int i = 0; i < adj[curr].size(); i++)
    {
        int next = adj[curr][i];
        if (capacity[curr][next] > 0 && not visited[next])
        {
            visited[next] = 1;
            dfs(capacity, next, adj, visited);
        }
    }

    return;
}

int main()
{
    int vertex, edge;
    cin >> vertex >> edge;
    // int capacity[vertex][vertex];
    //  vector<int> capacity[vertex](vertex);
    int **capacity = new int *[vertex];
    for (int i = 0; i < vertex; i++)
        capacity[i] = new int[vertex];
    vector<int> adj[vertex];
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
            capacity[i][j] = 0;
    }
    for (int i = 0; i < edge; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        capacity[a][b] = c;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int source, sink;
    cin >> source >> sink;
    source--;
    sink--;

    Output myoutput = maxflow(vertex, capacity, adj, source, sink);
    cout << "Answer:\n";
    cout << myoutput.maximum_flow_vertex << " " << myoutput.maximum_flow << endl;
    int **newcapacity = myoutput.capacity;
    // for (int i = 0; i < vertex; i++)
    // {
    //     for (int j = 0; j < vertex; j++)
    //     {
    //         cout << newcapacity[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    vector<int> visited(vertex, 0);
    visited[source] = 1;
    dfs(newcapacity, source, adj, visited);
    cout << "[{ ";
    for (int i = 0; i < vertex; i++)
    {
        if (visited[i] == 1)
        {
            cout << i + 1 << ",";
        }
    }
    cout << "}, {";
    for (int i = 0; i < vertex; i++)
    {
        if (visited[i] == 0)
        {
            cout << i + 1 << ",";
        }
    }
    cout << "}\n";
    cout << myoutput.sinkflow << endl;
}
