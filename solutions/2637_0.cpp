#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;;

const int MAXN = 105;

bool visited[MAXN], is_leaf[MAXN];
int n, m, dp[MAXN][MAXN];
vector<pii> graph[MAXN];

void dfs(int node) {
    if(visited[node]) return;
    visited[node] = true;
    is_leaf[node] = true;
    dp[node][node] = 1;
    for(auto [child, cnt] : graph[node]) {
        is_leaf[node] = false;

        dfs(child);
        for(int i = 1; i <= n; i++) dp[node][i] += cnt * dp[child][i];
    }
}

int main() {
    cin >> n;
    cin >> m;
    for(int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        graph[x].push_back({y, z});
    }

    dfs(n);

    for(int i = 1; i <= n; i++) {
        if(is_leaf[i]) cout << i << " " << dp[n][i] << "\n";
    }
}