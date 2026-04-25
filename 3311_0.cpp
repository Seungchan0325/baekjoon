#include <bits/stdc++.h>

using namespace std;

const int MAXN = 303030;
const int MAXM = 909090;

bool inStack[MAXN], reachable[MAXN];
int n, m, A, B, x[MAXN], y[MAXN], low[MAXN], num[MAXN], pv, scc[MAXN], scc_num, L[MAXN], R[MAXN];
stack<int> s;
vector<int> g[MAXN], rg[MAXN], fg[MAXN];

void dfs(int u)
{
    num[u] = low[u] = ++pv;
    inStack[u] = true;
    s.push(u);

    for(auto v : g[u]) {
        if(!num[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(inStack[v]) {
            low[u] = min(low[u], num[v]);
        }
    }

    if(num[u] == low[u]) {
        while(true) {
            int v = s.top(); s.pop();
            inStack[v] = false;
            scc[v] = scc_num;
            if(v == u) break;
        }
        scc_num++;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m >> A >> B;
    for(int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    for(int i = 1; i <= m; i++) {
        int u, v, k;
        cin >> u >> v >> k;
        g[u].push_back(v);
        if(k == 2) g[v].push_back(u);
    }

    for(int i = 1; i <= n; i++) {
        if(!num[i]) dfs(i);
    }

    for(int u = 1; u <= n; u++) {
        for(auto v : g[u]) {
            if(scc[u] == scc[v]) continue;
            fg[scc[u]].push_back(scc[v]);
            rg[scc[v]].push_back(scc[u]);
        }
    }

    for(int i = 0; i < scc_num; i++) L[i] = 1e9, R[i] = -1e9;

    for(int i = 1; i <= n; i++) {
        if(x[i] == 0) reachable[scc[i]] = true;
    }

    for(int i = scc_num-1; i >= 0; i--) {
        for(auto j : rg[i]) {
            reachable[i] |= reachable[j];
        }
    }

    vector<pair<int, int>> v;
    for(int i = 1; i <= n; i++) {
        if(x[i] == A && reachable[scc[i]]) {
            v.push_back({y[i], i});
        }
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++) {
        int x = scc[v[i].second];
        L[x] = min(L[x], i);
        R[x] = max(R[x], i);
    }
    for(int i = 0; i < scc_num; i++) {
        for(auto j : fg[i]) {
            L[i] = min(L[i], L[j]);
            R[i] = max(R[i], R[j]);
        }
    }
    v.clear();
    for(int i = 1; i <= n; i++) {
        if(x[i] == 0) {
            v.push_back({y[i], i});
        }
    }
    sort(v.begin(), v.end(), greater<>());
    for(auto [_, i] : v) {
        cout << max(R[scc[i]] - L[scc[i]] + 1, 0) << "\n";
    }
}
