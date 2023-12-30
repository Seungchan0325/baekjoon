#include <bits/stdc++.h>

using namespace std;

int root[51], ans[51];

int Find(int x)
{
    if(root[x] == x) return x;
    return root[x] = Find(root[x]);
}

bool Union(int x, int y)
{
    x = Find(x);
    y = Find(y);

    if(x == y) return false;

    root[y] = x;
    return true;
}

int main()
{
    int n, m;
    cin >> n >> m;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> edges;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            char c;
            cin >> c;
            if(c == 'Y' && i < j)
            {
                edges.emplace(i, j);
            }
        }
    }
    
    for(int i = 0; i < n; i++)
    {
        root[i] = i;
    }

    int linked = n - 1;
    vector<pair<int, int>> v;
    while(!edges.empty())
    {
        auto [i, j] = edges.top(); edges.pop();
        if(Union(i, j))
        {
            ans[i]++;
            ans[j]++;
            linked--;
        }
        else
        {
            v.emplace_back(i, j);
        }
    }

    if(linked || v.size() < m - n + 1)
    {
        cout << "-1";
        return 0;
    }

    for(int k = 0; k < m - n + 1; k++)
    {
        auto [i, j] = v[k];
        ans[i]++;
        ans[j]++;
    }

    for(int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }
}