#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 305;

ll n, m, x[MAXN], cache[MAXN][MAXN][2];

ll f(ll s, ll e, bool k, ll w)
{
    if(w == 0) return 0;
    ll& ret = cache[s][e][k];
    if(ret != -1) return ret;

    ret = 1e9;
    ll cur = k ? e : s;
    if(1 < s) ret = min(ret, f(s - 1, e, false, w - 1) + w * (x[cur] - x[s-1]));
    if(e < n) ret = min(ret, f(s, e + 1, true, w - 1) + w * (x[e+1] - x[cur]));
    return ret;
}

int main()
{
    cin >> n >> m;
    bool iszero = false;
    for(ll i = 1; i <= n; i++) {
        cin >> x[i];
        if(x[i] == 0) iszero = true;
    }

    if(!iszero) {
        x[n+1] = 0;
        n++;
    }

    sort(x + 1, x + n + 1);

    ll ans = 0;
    ll zero = lower_bound(x + 1, x + n + 1, 0) - x;
    assert(x[zero] == 0);
    for(ll i = 0; i <= n; i++) {
        memset(cache, -1, sizeof(cache));
        ans = max(ans, m * i - f(zero, zero, false, i));
        // prllf("%d\n", f(zero, zero, 0, i));
    }

    if(iszero) ans += m;

    cout << ans;
}