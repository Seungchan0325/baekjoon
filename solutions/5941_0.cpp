#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int n, s, up[MAXN], cut[MAXN];
vector<int> g[MAXN];

void dfs(int u, int p, int k)
{
    up[u] = cut[u] = 0;
    vector<int> a; a.reserve(g[u].size());
    for(auto v : g[u]) {
        if(v == p) continue;
        dfs(v, u, k);
        cut[u] += cut[v];
        a.push_back(up[v] + 1);
    }
    sort(a.begin(), a.end());
    int mx1 = 0;
    int mx2 = 0;
    for(int i = 0; i < a.size(); i++) {
        if(mx1 + a[i] > k) {
            cut[u] += ssize(a) - i;
            break;
        }
        mx2 = mx1;
        mx1 = a[i];
    }
    up[u] = mx1;
}

int main()
{
    cin >> n >> s;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int lo = 0;
    int hi = n;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        dfs(1, -1, mid);
        if(cut[1] > s) lo = mid;
        else hi = mid;
    }
    cout << hi << "\n";
}