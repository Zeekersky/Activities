#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

void dijkstra(vector<vector<int>> &adjacencyMat, int start, int vertices, vector<int> &distances)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    distances.resize(vertices, INT_MAX);

    distances[start] = 0;
    heap.push({0, start});

    while (!heap.empty())
    {
        int u = heap.top().second;
        int dist = heap.top().first;
        heap.pop();

        if (dist > distances[u])
        {
            continue;
        }

        for (int v = 0; v < vertices; ++v)
        {
            if (adjacencyMat[u][v] != 0 && dist + adjacencyMat[u][v] < distances[v])
            {
                distances[v] = dist + adjacencyMat[u][v];
                heap.push({distances[v], v});
            }
        }
    }
}

bool checkNegativeCycle(vector<vector<int>> &adjacencyMat, int vertices)
{
    vector<int> distances;
    dijkstra(adjacencyMat, 0, vertices, distances);

    vector<int> originalDistances = distances;
    dijkstra(adjacencyMat, 0, vertices, distances);

    for (int i = 0; i < vertices; ++i)
    {
        if (distances[i] < originalDistances[i])
        {
            cout << -1;
            return true; // Negative weight edge creates problem
        }
    }

    for (int i = 0; i < vertices; i++)
        cout << distances[i] << " ";
    return false;
}

int main()
{
    int vertices, edges;
    cin >> vertices >> edges;

    vector<vector<int>> adjacencyMat(vertices, vector<int>(vertices, 0));

    for (int i = 0; i < edges; ++i)
    {
        int u, v, weight;
        cin >> u >> v >> weight;
        adjacencyMat[u][v] = weight;
    }

    checkNegativeCycle(adjacencyMat, vertices);
    return 0;
}
