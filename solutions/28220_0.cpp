#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 105;
const ll INF = 1e18;

ll N, L, R, arr[MAXN], mn[MAXN], mx[MAXN], dp[MAXN][105][10005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> L >> R;
    for(ll i = 1; i <= N; ++i) {
        cin >> arr[i];
    }
    for(ll i = N; i >= 1; --i) {
        mn[i] = L - arr[i] + mn[i+1];
        mx[i] = R - arr[i] + mx[i+1];
        assert(0 <= mx[i] - mn[i] && mx[i] - mn[i] <= 10000);
    }

    fill((ll*)dp, (ll*)dp + sizeof(dp) / sizeof(ll), INF);
    if(0 < mn[1] || mx[1] < 0) goto NOT_FOUND;

    for(ll i = L; i <= R; ++i) {
        ll v = arr[1] - i;
        if(v < mn[2] || mx[2] < v) continue;
        dp[i-L+1][1][v-mn[2]] = abs(v);
    }

    for(ll i = L; i <= R; ++i) {
        for(ll j = 1; j <= N; ++j) {
            if(i == L && j == 1) continue;
            for(ll k = mn[j+1]; k <= mx[j+1]; ++k) {
                ll& cur = dp[i-L+1][j][k-mn[j+1]];

                ll cand = dp[i-L][j][k-mn[j+1]];
                cur = min(cand, cur);

                ll prv = k - (arr[j] - i);
                if(prv < mn[j] || mx[j] < prv) continue;

                cand = dp[i-L+1][j-1][prv-mn[j]] + abs(k);
                cur = min(cand, cur);
            }
        }
    }

    if(dp[R-L+1][N][0] >= INF) goto NOT_FOUND;
    cout << dp[R-L+1][N][0] << "\n";
    return 0;
NOT_FOUND:
    cout << "-1\n";
    return 0;
}