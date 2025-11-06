#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;
const int MAXK = 21;

int N, K, ans;
vector<int> g[MAXN];
array<int, MAXK> dp[MAXN];

void dfs(int u, int p)
{
    dp[u][0] = 1;
    for(auto v : g[u]) {
        if(v == p) continue;
        dfs(v, u);
        for(int i = 1; i < MAXK; i++) {
            dp[u][i] += dp[v][i-1];
        }
    }
}

void updfs(int u, int p, array<int, MAXK> updp)
{
    for(int i = 1; i < MAXK; i++) dp[u][i] += updp[i-1];
    int cnt = 0;
    for(int i = 0; i <= K; i++) cnt += dp[u][i];
    ans = max(ans, cnt);
    for(auto v : g[u]) {
        if(v == p) continue;
        array<int, MAXK> nxt = dp[u];
        for(int i = 1; i < MAXK; i++) {
            nxt[i] -= dp[v][i-1];
        }
        updfs(v, u, nxt);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> K;
    for(int i = 1; i < N; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1);
    updfs(1, -1, {});

    cout << ans << "\n";
}