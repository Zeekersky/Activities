#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

vector<int> parent, ranks;

int find(int x)
{
    if (parent[x] != x)
    {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

int mst(vector<pair<pair<int, int>, int>> &roads, int n, int k)
{
    parent.resize(n + 1);
    ranks.resize(n + 1);
    iota(parent.begin(), parent.end(), 0);
    fill(ranks.begin(), ranks.end(), 0);
    int count = 0;
    vector<int> costs;
    int total = 0;
    for (auto &road : roads)
    {
        int a = road.first.first;
        int b = road.first.second;
        int c = road.second;
        int pa = find(a);
        int pb = find(b);
        if (pa != pb)
        {
            costs.push_back(c);
            total += c;
            count++;
            if (ranks[pa] < ranks[pb])
            {
                parent[pa] = pb;
            }
            else if (ranks[pa] > ranks[pb])
            {
                parent[pb] = pa;
            }
            else
            {
                parent[pb] = pa;
                ranks[pa]++;
            }
        }
        if (count == n - 1)
        {
            break;
        }
    }
    reverse(costs.begin(), costs.end());
    int ans = -1;
    for (int i = 0; i < n - 1; ++i)
    {
        if (total <= k)
        {
            ans = i;
            break;
        }
        total -= costs[i];
    }
    return ans;
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<pair<int, int>, int>> roads;
    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        roads.push_back({{a, b}, c});
    }
    sort(roads.begin(), roads.end(), [](auto &left, auto &right)
         { return left.second < right.second; });
    int result = mst(roads, n, k);
    cout << result << endl;
    return 0;
}
