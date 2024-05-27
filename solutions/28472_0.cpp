#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int MAXN = 1e5 + 10;

int N, R, L, Q, dp[MAXN];
vector<int> g[MAXN];

void mxdfs(int u, int p);

void mndfs(int u, int p)
{
    if(p == -1 || g[u].size() != 1) dp[u] = INF;
    for(auto v : g[u]) {
        if(v == p) continue;
        mxdfs(v, u);
        dp[u] = min(dp[u], dp[v]);
    }
}
void mxdfs(int u, int p)
{
    if(p == -1 || g[u].size() != 1) dp[u] = -INF;
    for(auto v : g[u]) {
        if(v == p) continue;
        mndfs(v, u);
        dp[u] = max(dp[u], dp[v]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> R;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cin >> L;
    for(int i = 0; i < L; i++) {
        int k, t;
        cin >> k >> t;
        dp[k] = t;
    }

    mxdfs(R, -1);

    cin >> Q;
    while(Q--) {
        int q;
        cin >> q;
        cout << dp[q] << "\n";
    }
}