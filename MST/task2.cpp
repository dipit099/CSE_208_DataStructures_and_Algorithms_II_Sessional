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

int cc = 0;

bool compare(Edge e1, Edge e2)
{
    if (e1.weight == e2.weight)
    {
        return e1.start < e2.start;
    }
    return e1.weight < e2.weight;
}
bool compareindex(Edge e1, Edge e2)
{

    return e1.index < e2.index;
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

void allcombo(Edge graph[], bool check[], int lowsum, int tempsum, int vertex, int edgeindex, int totaledge, int curredge, int countno[])
{
    if (tempsum > lowsum || curredge > vertex - 1 || edgeindex > totaledge)
    {
        return;
    }

    else if (tempsum == lowsum && curredge == vertex - 1)
    {
        bool loop = false;
        int parent[vertex + 1];
        for (int i = 0; i <= vertex; i++)
        {
            parent[i] = -1;
        }
        for (int i = 0; i < totaledge; i++)
        {
            if (check[i] == true)
            {
                int start = graph[i].start;
                int end = graph[i].end;
                if (checkunion(parent, start, end) == false)
                {
                    loop = true;
                    // cout << "loop\n";
                    break;
                }
            }
        }
        if (loop == false)
        {
            cc++;
            for (int i = 0; i < totaledge; i++)
            {
                if (check[i] == true)
                {
                    Edge e = graph[i];
                    countno[e.index]++;
                }
            }
           
        }
        return;
    }

    check[edgeindex] = true;
    allcombo(graph, check, lowsum, tempsum + graph[edgeindex].weight, vertex, edgeindex + 1, totaledge, curredge + 1, countno);
    check[edgeindex] = false;
    allcombo(graph, check, lowsum, tempsum, vertex, edgeindex + 1, totaledge, curredge, countno);

    return;
}

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int vertex, edge;
    cin >> vertex >> edge;
    Edge graph[edge];
    bool check[edge];
    int parent[vertex + 1];
    int countno[edge];
    for (int i = 0; i <= vertex; i++)
    {

        parent[i] = -1;
    }

    for (int i = 0; i < edge; i++)
    {
        int start, end, weight;
        cin >> start >> end >> weight;
        graph[i] = Edge(start, end, weight, i);
        check[i] = false;
        countno[i] = 0;       
    }
    sort(graph, graph + edge, compare);
    // for (int i = 0; i < edge; i++)
    // {
    //     cout << graph[i].start << " " << graph[i].end << " " << graph[i].weight << endl;
    // }

    int lowsum = 0;

    for (int i = 0; i < edge; i++)
    {
        int start = graph[i].start;
        int end = graph[i].end;
        int weight = graph[i].weight;
        if (checkunion(parent, start, end))
        {
            lowsum += weight; /// only find min weight
            // cout << lowsum << endl;
        }
    }
    
    for (int j = 0; j < edge; j++)
    {
        allcombo(graph, check, lowsum, 0, vertex, j, edge, 0, countno);
    }
    sort(graph, graph + edge, compareindex);
    for (int i = 0; i < edge; i++)
    {
        if (countno[i] == cc)
        {
            cout << "any\n";
        }
        else if (countno[i] == 0)
        {
            cout << "none\n";
        }
        else
        {
            cout << "at least one\n";
        }
    }
}
