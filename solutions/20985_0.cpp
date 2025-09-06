#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;
const ll INF = 1e18;

int N, Q;
ll X[MAXN], W[MAXN], MX[MAXN], MN[MAXN], ans[MAXN];

int inter(ll x1, ll x2)
{
    if(x1 > x2) swap(x1, x2);
    int lo = 0;
    int hi = Q+1;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(x1 + MX[mid] < x2 + MN[mid]) lo = mid;
        else hi = mid;
    }
    return lo;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(int i = 1; i <= N; i++) cin >> X[i];
    for(int i = 1; i <= Q; i++) cin >> W[i];

    ll p = 0;
    for(int i = 1; i <= Q; i++) {
        p += W[i];
        MN[i] = min(MN[i-1], p);
        MX[i] = max(MX[i-1], p);
    }

    X[0] = -INF;
    X[N+1] = INF;
    for(int i = 1; i <= N; i++) {
        int l = inter(X[i-1], X[i]);
        int r = inter(X[i], X[i+1]);
        ans[i] = MX[r] - MN[l];
        if(l+1 <= Q && W[l+1] < 0) ans[i] += (X[i] + MN[l]) - (X[i-1] + MX[l]);
        if(r+1 <= Q && W[r+1] > 0) ans[i] += (X[i+1] + MN[r]) - (X[i] + MX[r]);
    }

    for(int i = 1; i <= N; i++) {
        cout << ans[i] << "\n";
    }
}