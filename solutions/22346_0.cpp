#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll N, Q;
map<ll, ll> memL[10101], memR[10101], memA[10101];

ll Z(ll l, ll r, ll s, ll e, ll idx)
{
    if(e < l || r < s) return 0;
    if(idx == 1) return 0;
    ll m = (s + e) / 2;
    if(l <= s && e <= r) {
        int lg = 64-countl_zero((unsigned ll)idx);
        return idx ^ ((1LL<<lg)-1);
    }
    ll ret = Z(l, r, s, m-1, idx/2) + Z(l, r, m+1, e, idx/2);
    if(l <= m && m <= r) ret += ~idx&1;
    return ret;
}

ll L(ll l, ll r, ll k, ll s, ll e, ll idx)
{
    if(e < l || r < s) return 0;
    if(idx == 1) return 1;
    if(l <= s && e <= r && memL[k].contains(idx)) {
        return memL[k][idx];
    }
    ll m = (s + e) / 2;
    ll ret = L(l, r, k, s, m-1, idx/2);
    if(l <= m && m <= r) {
        ll kp = Z(l, r, s, m-1, idx/2);
        if(k-kp-(~idx&1) >= 0) ret = m-max(l,s)+1+L(l, r, k-kp-(~idx&1), m+1, e, idx/2);
    }
    if(l <= s && e <= r) memL[k][idx] = ret;
    return ret;
}

ll R(ll l, ll r, ll k, ll s, ll e, ll idx)
{
    if(e < l || r < s) return 0;
    if(idx == 1) return 1;
    if(l <= s && e <= r && memR[k].contains(idx)) {
        return memR[k][idx];
    }
    ll m = (s + e) / 2;
    ll ret = R(l, r, k, m+1, e, idx/2);
    if(l <= m && m <= r) {
        ll kp = Z(l, r, m+1, e, idx/2);
        if(k-kp-(~idx&1) >= 0) ret = min(r,e)-m+1+R(l, r, k-kp-(~idx&1), s, m-1, idx/2);
    }
    if(l <= s && e <= r) memR[k][idx] = ret;
    return ret;
}

ll A(ll l, ll r, ll k, ll s, ll e, ll idx)
{
    if(e < l || r < s) return 0;
    if(idx == 1) return 1;
    ll m = (s + e) / 2;
    if(l <= s && e <= r) {
        if(memA[k].contains(idx)) return memA[k][idx];
    }
    ll ret = max(A(l, r, k, s, m-1, idx/2), A(l, r, k, m+1, e, idx/2));
    if(l <= m && m <= r) {
        for(ll kp = 0; k-kp-(~idx&1) >= 0; kp++) {
            ret = max(ret, R(l, r, kp, s, m-1, idx/2) + L(l, r, k-kp-(~idx&1), m+1, e, idx/2) + 1);
        }
    }
    if(l <= s && e <= r) memA[k][idx] = ret;
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    int lg = 64-countl_zero((unsigned ll)N);
    ll len = (1LL<<lg)-1;
    while(Q--) {
        ll i, j, k;
        cin >> i >> j >> k;
        ll ans = A(i, j, k, 1, len, N);
        cout << ans << "\n";
    }
}