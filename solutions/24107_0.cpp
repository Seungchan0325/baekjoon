#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;
ll n, p[MAXN], a[MAXN], seg[MAXN<<1];

void upd(int x, ll v)
{
    x+=MAXN;
    seg[x] = max(seg[x], v);
    while(x>>=1) seg[x] = max(seg[x<<1], seg[x<<1|1]);
}

ll qry(int l, int r)
{
    ll ret = 0;
    for(l+=MAXN, r+=MAXN; l<=r; l>>=1, r>>=1) {
        if(l&1) ret = max(ret, seg[l++]);
        if(~r&1) ret = max(ret, seg[r--]);
    }
    return ret;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> p[i];
    ll mx = 0;
    for(int i = 1; i <= n; i++) {
        ll dp = qry(1, p[i]) + a[p[i]];
        mx = max(mx, dp);
        upd(p[i], dp);
    }

    ll ans = 0;
    for(int i = 1; i <= n; i++) ans += a[i]<<1;
    ans -= mx<<1;
    cout << ans;
}