#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ipair;

class Edge
{
public:
    int start, end, weight;
    Edge() {}
    Edge(int start, int end, int weight)
    {
        this->start = start;
        this->end = end;
        this->weight = weight;
    }
};

ipair findBellmanWeight(Edge edges[], int vertex, int edge, int src, int dest, int prevdesc)
{
    int dist[vertex];
    for (int i = 0; i < vertex; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;
    // cout << "src: " << src << " dest: " << dest << endl;
    for (int i = 1; i <= vertex - 1; i++)
    {
        for (int j = 0; j < edge; j++)
        {
            int start = edges[j].start;
            int end = edges[j].end;
            int weight = edges[j].weight;
            if (dist[start] != INT_MAX && dist[start] + weight < dist[end])
            {
                dist[end] = dist[start] + weight;
                // cout << "start && end " << start << ' ' << end << endl;
            }
        }
    }
    ipair p = make_pair(dist[dest], dist[prevdesc]); // returns dest and prevdesc
    return p;
}
int main()
{
    int n, m;
    cin >> n >> m;
    Edge edges[m + 1];
    for (int i = 0; i < m; i++)
    {
        int start, end, weight;
        cin >> start >> end >> weight;
        // edges[i] = Edge(start, end, weight);
        edges[i] = Edge(start - 1, end - 1, weight);
    }
    int A, B;
    cin >> A >> B;
    A--;
    B--;
    int L, H;
    cin >> L >> H;
    int src, dest;
    cin >> src >> dest;
    src--;
    dest--;
    ipair minwght = findBellmanWeight(edges, n, m, src, dest, A);
    // cout << "MIN WEIGHT: " << minwght << endl;
    ipair cycleweight = findBellmanWeight(edges, n, m, B, A, dest);
    // cout << "CYCLE WEIGHT: " << cycleweight.first << endl;

    if (cycleweight.first == INT_MAX) // add edge any weight
    {
        if (minwght.second + L + cycleweight.second < minwght.first)
        {
            cout << L << ' ' << minwght.second + L + cycleweight.second;
        }

        else
        {
            cout << "impossible\n";
        }
    }
    else
    {
        int edgevalue = -cycleweight.first; // u can only add this weight to avoid neg cycle

        if (edgevalue >= L && edgevalue <= H)
        {

            if (minwght.second + edgevalue + cycleweight.second < minwght.first)
            {
                cout << edgevalue << ' ' << minwght.second + edgevalue + cycleweight.second;
            }
            else
            {
                cout << "impossible\n";
            }
        }
        else if (edgevalue < L)
        {
            if (minwght.second + L + cycleweight.second < minwght.first)
            {
                cout << L << ' ' << minwght.second + L + cycleweight.second;
            }
            else
            {
                cout << "impossible\n";
            }
        }
        else
        {
            cout << "impossible\n";
        }
    }
}