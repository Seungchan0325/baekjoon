#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int LOGN = 17;

int N, M, par[LOGN+1][MAXN], dep[MAXN];
vector<int> graph[MAXN];

void dfs(int u, int p)
{
    for(int i = 1; i <= LOGN; i++) {
        par[i][u] = par[i-1][par[i-1][u]];
    }
    for(auto v : graph[u]) {
        if(v == p) continue;

        dep[v] = dep[u] + 1;
        par[0][v] = u;
        dfs(v, u);
    }
}

int LCA(int u, int v)
{
    if(dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for(int i = 0; i <= LOGN; i++) {
        if(diff&(1<<i)) {
            u = par[i][u];
        }
    }

    if(u == v) return u;

    for(int i = LOGN; i >= 0; i--) {
        if(par[i][u] != par[i][v]) {
            u = par[i][u];
            v = par[i][v];
        }
    }
    return par[0][u];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, -1);

    cin >> M;
    while(M--) {
        int r, u, v;
        cin >> r >> u >> v;

        pair<int, int> mx;
        int lca = LCA(u, v);
        mx = max(make_pair(dep[lca], lca), mx);
        lca = LCA(u, r);
        mx = max(make_pair(dep[lca], lca), mx);
        lca = LCA(r, v);
        mx = max(make_pair(dep[lca], lca), mx);
        cout << mx.second << "\n";
    }
}