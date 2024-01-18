#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1e5 + 5;

int n, m, dp[2][MAXN], p[MAXN];
vector<int> adj[MAXN];

void dfs(int node, int v) {
    dp[0][node] = v;
    dp[1][node] = v ^ 1;
    for(auto child : adj[node]) {
        if(child == p[node]) continue;

        p[child] = node;
        dfs(child, v ^ 1);
        
        dp[0][node] += dp[0][child];
        dp[1][node] += dp[1][child];
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n>>m;
    for(int i=1; i<n; i++) {
        int u, v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 1);

    while(m--) {
        int u, v, c;
        cin>>u>>v>>c;

        ll ans = 0;
        if(p[v] == u) {
            //ans += start * end;
            ans += (ll)(dp[0][1] - dp[0][v]) * (ll)dp[c][v];
            //printf("when node 1 is red\n");
            //printf("start: %d\n", (ll)(dp[0][1] - dp[0][v]));
            //printf("end: %d\n", (ll)dp[c][v]);
            
            ans += (ll)(dp[1][1] - dp[1][v]) * (ll)dp[c^1][v];
            //printf("when node 1 is black\n");
            //printf("start: %d\n", (ll)(dp[1][1] - dp[1][v]));
            //printf("end: %d\n", (ll)dp[c^1][v]);
        } else if(p[u] == v) {
            ans += (ll)dp[0][u] * (ll)(dp[c][1] - dp[c][u]);
            //printf("when node 1 is red\n");
            //printf("start: %d\n", (ll)dp[0][u]);
            //printf("end: %d\n", (ll)(dp[c][v] - dp[c][u]));

            ans += (ll)dp[1][u] * (ll)(dp[c^1][1] - dp[c^1][u]);
            //printf("when node 1 is black\n");
            //printf("start: %d\n", (ll)dp[1][u]);
            //printf("end: %d\n", (ll)(dp[c^1][v] - dp[c^1][u]));
        } else {
            assert(0);
        }
        cout<<ans<<"\n";
    }
}