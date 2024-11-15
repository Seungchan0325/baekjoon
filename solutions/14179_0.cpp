#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using pii = pair<ll, ll>;

const ll MAXN = 5050;

ll N, K, X[MAXN], W[MAXN], C[MAXN][MAXN], SW[MAXN], SXW[MAXN], DP[MAXN][MAXN];

void DnC(ll k, ll l, ll r, ll optL, ll optR)
{
    if(r < l) return;

    ll m = (l + r) / 2;
    ll opt = 1e18;
    ll optI = -1;
    for(ll i = optL; i <= min(optR, m); i++) {
        ll cand = DP[k-1][i-1] + C[i][m];
        if(cand < opt) {
            opt = cand;
            optI = i;
        }
    }

    DP[k][m] = opt;

    DnC(k, l, m-1, optL, optI);
    DnC(k, m+1, r, optI, optR);
}

ll compute(int l, int r, int i)
{
    return (SW[i] - SW[l-1]) * X[i] - (SXW[i] - SXW[l-1]) + (SXW[r] - SXW[i-1]) - X[i] * (SW[r] - SW[i-1]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;
    vector<pii> stores(N);
    for(auto& [x, w] : stores) cin >> x >> w;
    sort(stores.begin(), stores.end());
    for(ll i = 0; i < N; i++) {
        X[i+1] = stores[i].first;
        W[i+1] = stores[i].second;
    }

    for(ll i = 1; i <= N; i++) {
        SW[i] = SW[i-1] + W[i];
        SXW[i] = SXW[i-1] + X[i] * W[i];
    }

    for(ll l = 1; l <= N; l++) {
        ll optI = l;
        for(ll r = l; r <= N; r++) {
            while(optI < r && compute(l, r, optI+1) < compute(l, r, optI)) optI++;
            C[l][r] = compute(l, r, optI);
        }
    }

    for(ll i = 1; i <= N; i++) DP[0][i] = 1e18;

    // for(ll k = 1; k <= K; k++) {
    //     for(int i = 1; i <= N; i++) {
    //         ll cand = 1e9;
    //         for(int j = 1; j <= i; j++) {
    //             cand = min(cand, DP[k-1][j-1] + C[j][i]);
    //         }
    //         DP[k][i] = cand;
    //     }
    // }

    for(ll k = 1; k <= K; k++) {
        DnC(k, 1, N, 1, N);
    }

    cout << DP[K][N];
}