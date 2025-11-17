#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")

#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 10101;
const int MAXS = 25050;
const int MAXK = 105;
const int inf = 1e18;

bool vst[MAXN][MAXK];
int n, m, s, k, t, l[MAXS], x[MAXS], y[MAXS];
vector<int> v[MAXS], arrive[MAXS], dp[MAXS][MAXK];
vector<pair<int, int>> r[MAXN];
unordered_map<int, int> mat[MAXN];

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m >> s >> k >> t;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        mat[u][v] = mat[v][u] = w;
    }
    for(int i = 1; i <= s; i++) {
        cin >> l[i] >> x[i] >> y[i];
        v[i].resize(l[i]);
        arrive[i].resize(l[i]);
        for(int j = 0; j < MAXK; j++) dp[i][j].resize(l[i], inf);
        for(int j = 0; j < l[i]; j++) {
            cin >> v[i][j];
            r[v[i][j]].emplace_back(i, j);
        }
        arrive[i][0] = x[i];
        for(int j = 1; j < l[i]; j++) {
            arrive[i][j] = arrive[i][j-1] + mat[v[i][j-1]][v[i][j]];
        }
    }

    l[0] = 1;
    v[0] = {1};
    for(int j = 0; j < MAXK; j++) dp[0][j] = {inf};
    dp[0][k+1][0] = t;

    priority_queue<tuple<int, int, int, int>> pq;

    pq.emplace(-t, 0, k+1, 0);
    while(!pq.empty()) {
        auto [d, route, transfer, i] = pq.top(); pq.pop();
        d = -d;
        if(d > dp[route][transfer][i]) continue;
        int u = v[route][i];
        if(transfer > 0 && !vst[u][transfer-1]) {
            // vst[u][transfer-1] = true;
            for(int tr = 0; tr < transfer; tr++) vst[u][tr] = true;
            for(auto [nxt, j] : r[u]) {
                int a = arrive[nxt][j];
                int k = max<int>((d - a + y[nxt] - 1) / y[nxt], 0);
                int nd = a + k * y[nxt];
                if(dp[nxt][transfer-1][j] > nd) {
                    dp[nxt][transfer-1][j] = nd;
                    pq.emplace(-nd, nxt, transfer-1, j);
                }
            }
        }

        if(i+1 < l[route]) {
            int nd = d + mat[v[route][i]][v[route][i+1]];
            if(dp[route][transfer][i+1] > nd) {
                dp[route][transfer][i+1] = nd;
                pq.emplace(-dp[route][transfer][i+1], route, transfer, i+1);
            }
        }
    }

    int ans = inf;
    for(auto [i, j] : r[n]) {
        for(int k = 0; k < MAXK; k++) {
            ans = min(ans, dp[i][k][j]);
        }
    }
    if(ans >= inf) cout << "NIE\n";
    else cout << ans << "\n";
}