#include <bits/stdc++.h>

using namespace std;

const int MAXV = 100005;

int V, ans;
vector<pair<int, int>> g[MAXV];

int dfs(int u, int p)
{
    vector<int> ch;
    ch.push_back(0); // dummy
    ch.push_back(0);
    for(auto [v, d] : g[u]) {
        if(v == p) continue;
        ch.push_back(dfs(v, u) + d);
    }

    sort(ch.begin(), ch.end(), greater<>());

    ans = max(ch[0] + ch[1], ans);

    return ch[0];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> V;
    for(int i = 1; i <= V; i++) {
        int u; cin >> u;
        while(true) {
            int v, d;
            cin >> v;
            if(v == -1) break;
            cin >> d;
            g[u].emplace_back(v, d);
            // g[v].emplace_back(u, d);
        }
    }

    dfs(1, -1);

    cout << ans;
}