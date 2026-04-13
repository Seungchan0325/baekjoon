#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 3030;
const int mod = 1e9 + 7;

int N, DP[MAXN][MAXN], pv;
vector<pair<int, int>> LR;

void dfs(int u, int pn)
{
    pv++;
    vector<int> v;
    while(pv < N && LR[pv].second < LR[u].second) {
        v.push_back(pv);
        dfs(pv, pn+1);
    }
    for(int j = 1; j <= pn+1; j++) {
        ll X = j;
        ll Y = mod-1; // -1
        for(int i : v) {
            X = X * DP[i][j+1] % mod;
            Y = Y * DP[i][j] % mod;
        }
        DP[u][j] = (X+Y) % mod;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T; cin >> T;
    while(T--) {
        cin >> N;
        LR.resize(N);
        for(auto& [l, r] : LR) cin >> l >> r;
        sort(LR.begin(), LR.end());

        pv = 0;
        ll ans = 1;
        while(pv < N) {
            int v = pv;
            dfs(pv, 0);
            ans = ans * DP[v][1] % mod;
        }

        cout << ans << "\n";
    }
}
