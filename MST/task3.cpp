#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int start, end, weight, index;
    Edge() {}
    Edge(int start, int end, int weight, int index)
    {
        this->start = start;
        this->end = end;
        this->weight = weight;
        this->index = index;
    }
};

bool compare(Edge e1, Edge e2)
{
    if (e1.weight == e2.weight)
    {
        return e1.start < e2.start;
    }
    return e1.weight < e2.weight;
}

int findparent(int parent[], int vertex)
{
    if (parent[vertex] == -1)
    {
        return vertex;
    }
    return parent[vertex] = findparent(parent, parent[vertex]);
}

bool checkunion(int parent[], int start, int end)
{
    int startparent = findparent(parent, start);
    int endparent = findparent(parent, end);
    if (startparent != endparent)
    {
        parent[startparent] = endparent;
        return true;
    }
    return false;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int vertex, edge;
    cin >> vertex >> edge;
    Edge graph[edge];
    bool check[edge];
    int parent[vertex + 1];
    for (int i = 0; i <= vertex; i++)
    {
        parent[i] = -1;
    }

    int countno[edge];

    for (int i = 0; i < edge; i++)
    {
        int start, end, weight;
        cin >> start >> end >> weight;
        graph[i] = Edge(start, end, weight, i);
        check[i] = false;
        countno[i] = 0;
    }
    sort(graph, graph + edge, compare);

    int lowsum = 0;

    for (int i = 0; i < edge; i++)
    {
        int start = graph[i].start;
        int end = graph[i].end;
        int weight = graph[i].weight;
        if (checkunion(parent, start, end))
        {
            lowsum += weight;
        }
    }

    vector<int> critical;
    vector<int> psedocritical;

    for (int i = 0; i < edge; i++)
    {
        // letsnot take edge i
        int tempsum = 0, countedge = 0;
        for (int j = 0; j <= vertex; j++)
        {
            parent[j] = -1;
        }

        for (int j = 0; j < edge; j++)
        {
            if (i != j)
            {
                int start = graph[j].start;
                int end = graph[j].end;
                int weight = graph[j].weight;
                if (checkunion(parent, start, end))
                {
                    tempsum += weight;
                }
            }
        }
        if (tempsum != lowsum)
        {
            critical.push_back(graph[i].index);
        }
        else
        {
            // lets take ith edge
            for (int j = 0; j <= vertex; j++)
            {
                parent[j] = -1;
            }
            int start = graph[i].start;
            int end = graph[i].end;
            int weight = graph[i].weight;
            tempsum = weight;
            parent[start] = end;
            countedge = 1;
            for (int j = 0; j < edge; j++)
            {
                if (i != j)
                {
                    int start = graph[j].start;
                    int end = graph[j].end;
                    int weight = graph[j].weight;
                    if (checkunion(parent, start, end))
                    {
                        tempsum += weight;
                        countedge++;
                    }
                }
            }
            if (tempsum == lowsum && countedge == vertex - 1)
            {
                psedocritical.push_back(graph[i].index);
            }
        }
    }
    cout << "Critical edges: [ ";
    for (auto itr : critical)
    {
        cout << itr << ",";
    }
    cout << "]";
    cout << endl;
    cout << "Psedo critical edge: [ ";
    sort(psedocritical.begin(), psedocritical.end());
    for (auto itr : psedocritical)
    {
        cout << itr << ",";
    }
    cout << "]";
    cout << endl;
}
