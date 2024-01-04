#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 10000;

bool visited[MAXN];
int n, sz[MAXN];
vector<pair<int, int>> adjlist[MAXN];

ll dfs(int node) {
    visited[node] = true;

    ll ret = 0;
    sz[node] = 1;
    for(auto [child, w] : adjlist[node]) {
        if(visited[child]) continue;

        ret += dfs(child);
        ret += w * sz[child];
        sz[node] += sz[child];
    }

    return ret;
}

ll minCost(int node, ll sum) {
    visited[node] = true;

    ll ret = sum;
    for(auto [child, w] : adjlist[node]) {
        if(visited[child]) continue;
        ret = min(minCost(child, sum + w * (n - 2 * sz[child])), ret);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    while(true) {
        cin>>n;
        if(n == 0) break;

        for(int i=0; i<n-1; i++) {
            int a, b, w; cin>>a>>b>>w;
            adjlist[a].push_back({b, w});
            adjlist[b].push_back({a, w});
        }


        memset(visited, 0, sizeof(visited));
        ll start = dfs(0);
        memset(visited, 0, sizeof(visited));
        ll ans = minCost(0, start);

        cout<<ans<<"\n";

        for(int i=0; i<=n; i++)
            adjlist[i].clear();
    }
}