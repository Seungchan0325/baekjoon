#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 5005;

ll N, K, A[MAXN], DP[MAXN][MAXN], OR[MAXN][MAXN];

void DnC(ll k, ll s, ll e, ll l, ll r)
{
    if(e < s) return;

    ll m = (s + e) / 2;
    ll mx = -1;
    ll mxi = -1;
    for(ll i = min(m, r); i >= l; i--) {
        if(i < k-1) break;
        ll cand = DP[k-1][i-1] + OR[i][m];
        if(cand > mx) {
            mx = cand;
            mxi = i;
        }
    }
    DP[k][m] = mx;

    DnC(k, s, m-1, l, mxi);
    DnC(k, m+1, e, mxi, r);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;
    for(ll i = 1; i <= N; i++) {
        cin >> A[i];
    }

    for(ll i = 1; i <= N; i++) {
        ll sum = 0;
        for(ll j = i; j <= N; j++) {
            sum |= A[j];
            OR[i][j] = sum;
        }
    }

    for(ll k = 1; k <= K; k++) {
        DnC(k, 1, N, 1, N);
    }

    cout << DP[K][N];
}