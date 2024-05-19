#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 2005;
const ll INF = 1e9;

ll N, delta, t[MAXN], p[MAXN], dp[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(ll i = 0; i < N; i++) {
        cin >> t[i] >> p[i];
    }
    cin >> delta;

    dp[0] = 1;
    for(ll i = 1; i < N; i++) {
        dp[i] = INF;
        ll mnn = -INF, mnd = 1;
        ll mxn = INF, mxd = 1;
        for(ll j = i - 1; j >= 0; j--) {
            ll n = -(p[j] - p[i]);
            ll d = -(t[j] - t[i]);
            if(mnn * d <= n * mnd && n * mxd <= mxn * d) {
                dp[i] = min(dp[j] + 1, dp[i]);
            }
 
            n = -(p[j] + delta - p[i]);
            if(mnn * d <= n * mnd) {
                mnn = n;
                mnd = d;
            }

            n = -(p[j] - delta - p[i]);
            if(n * mxd <= mxn * d) {
                mxn = n;
                mxd = d;
            }
        }
    }

    cout << dp[N-1];
}