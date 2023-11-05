#include <bits/stdc++.h>
using namespace std;

int adjacencyMat[100][100];

int dfsVisit(int v, int visited[], int stackk[], int num)
{
    visited[v] = 1;
    stackk[v] = 1;
    for (int i = 0; i < num; i++)
    {
        if (adjacencyMat[v][i])
        {
            if (!visited[i] && dfsVisit(i, visited, stackk, num))
                return 1;
            else if (stackk[i])
                return 1;
        }
    }
    stackk[v] = 0;
    return 0;
}

int dfs(int num)
{
    int visited[num], stk[num];
    for (int i = 0; i < num; i++)
        visited[i] = 0;

    for (int i = 0; i < num; i++)
    {
        if (!visited[i])
        {
            if (dfsVisit(i, visited, stk, num))
                return 1;
        }
    }
    return 0;
}

int main()
{
    int studNum, dependNum;
    cin >> studNum >> dependNum;

    // Initialization
    for (int i = 0; i < studNum; i++)
    {
        for (int j = 0; j < studNum; j++)
            adjacencyMat[i][j] = 0;
    }

    int a, b;
    for (int i = 0; i < dependNum; i++)
    {
        cin >> a >> b;
        adjacencyMat[a][b] = 1;
    }

    if (dfs(studNum))
        cout << -1;
    else
        cout << 1;
}