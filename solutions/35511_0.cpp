#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#define int long long

const int MAXN = 303030;

int N, M, dp[MAXN];
vector<pair<int, int>> rg[MAXN];

int run(int k)
{
    dp[1] = 0;
    for(int i = 2; i <= N; i++) {
        dp[i] = 1e9;
        for(auto [j, w] : rg[i]) {
            if(w < k) dp[i] = min(dp[i], dp[j]-1);
            else if(w < k+20) dp[i] = min(dp[i], dp[j]+(1ll<<(w-k))-1);
        }
    }
    return dp[N];
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;
        rg[v].push_back({u, i});
    }

    int lo = -1;
    int hi = 1e14;
    while(lo+1 < hi) {
        int mid = (lo+hi) / 2;
        if(run(mid+1) < 0) hi = mid;
        else lo = mid;
    }
    cout << hi << "\n";
}
