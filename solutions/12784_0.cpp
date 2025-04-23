#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;
const int MAXD = 25;

int N, M;
vector<pair<int, int>> g[MAXN];

int dfs(int u, int p)
{
    bool has_child = false;
    int ret = 0;
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        has_child = true;
        ret += min(dfs(v, u), w);
    }
    if(!has_child) ret = 1e5;
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        cin >> N >> M;
        for(int i = 1; i <= M; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        if(N == 1) {
            cout << "0\n";
            continue;
        }
        cout << dfs(1, -1) << "\n";
        for(int i = 1; i <= N; i++) g[i].clear();
    }
}