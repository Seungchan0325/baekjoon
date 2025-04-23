#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int N, R, Q, sz[MAXN];
vector<int> g[MAXN];

void dfs(int u, int p)
{
    sz[u] = 1;
    for(auto v : g[u]) {
        if(v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> R >> Q;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(R, -1);
    while(Q--) {
        int u;
        cin >> u;
        cout << sz[u] << "\n";
    }
}