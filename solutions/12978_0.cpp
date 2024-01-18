#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, dp[2][MAXN];
vector<int> childs[MAXN];

void dfs(int node, int parent) {
    dp[1][node] = 1;
    for(auto child : childs[node]) {
        if(child == parent) continue;

        dfs(child, node);

        dp[1][node] += min(dp[0][child], dp[1][child]);
        dp[0][node] += dp[1][child];
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=0; i<n-1; i++) {
        int u, v; cin>>u>>v;
        childs[u].push_back(v);
        childs[v].push_back(u);
    }

    dfs(1, -1);

    cout<<min(dp[0][1], dp[1][1]);
}