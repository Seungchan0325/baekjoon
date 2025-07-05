#include <bits/stdc++.h>

using namespace std;

const int MAXN = 15050;

int n, m, num[MAXN], low[MAXN], pv;
vector<int> g[MAXN];

int dfs(int u, int p)
{
    int ret = 0;
    num[u] = low[u] = ++pv;
    for(auto v : g[u]) {
        if(v == p) continue;
        if(!num[v]) {
            ret += dfs(v, u);

            if(low[v] > num[u]) {
                ret++;
                low[v] = 1;
            }

            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], num[v]);
    }
    return ret;
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        n++;
        g[u].push_back(n);
        g[n].push_back(u);
        g[v].push_back(n);
        g[n].push_back(v);
    }
    
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        pv = 0;
        memset(num, 0, sizeof(num));
        memset(low, 0, sizeof(low));
        int tmp = dfs(i, -1);
        ans = max(ans, tmp);
    }
    cout << (ans+1) / 2;
}