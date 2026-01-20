#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

const int MAXN = 505050;
const ll inf = 1e18;

struct SegTree {
    int n;
    vector<pair<ll, ll>> t;
    void init(int _n) {
        n = _n;
        t.resize(2*n);
        for(int i = 0; i < n; i++) t[i+n] = {0, i};
        for(int i = n-1; i > 0; i--) t[i] = min(t[i<<1], t[i<<1|1]);
    }
    void update(int x, ll v) {
        x += n;
        t[x].first = v;
        while(x>>=1) {
            t[x] = min(t[x<<1], t[x<<1|1]);
        }
    }
    pair<ll, ll> query(int l, int r) {
        pair<ll, ll> ret = {inf, -1};
        for(l+=n, r+=n; l <= r; l>>=1, r>>=1) {
            if(l&1) ret = min(ret, t[l++]);
            if(~r&1) ret = min(ret, t[r--]);
        }
        return ret;
    }
};

ll N, K, h[MAXN], lef[MAXN], rig[MAXN], holes[MAXN], pv;
SegTree seg;
ll rem;

ld dnc(int l, int r, int ph)
{
    if(r < l) return 0;
    int m = seg.query(l, r).second;
    int num = holes[r] - holes[l-1];
    if(!num) {
        for(int i = l; i <= r; i++) {
            rem += (rig[i] - lef[i]) * (h[i] - ph);
        }
        return 0;
    } else {
        return (ld)(rig[r] - lef[l]) * (h[m] - ph) / num + max(dnc(l, m-1, h[m]), dnc(m+1, r, h[m]));
    }
}

int main()
{
    cin >> N;
    ll x, y;
    x = y = 0;
    vector<array<ll, 4>> lines;
    for(int i = 0; i < N; i++) {
        ll nx, ny;
        cin >> nx >> ny;
        if(x == nx) {
            y = ny;
        } else {
            pv++;
            h[pv] = y;
            lef[pv] = x;
            rig[pv] = nx;
            lines.push_back({x, y, nx, ny});
            x = nx;
        }
    }
    cin >> K;
    for(int i = 0; i < K; i++) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        int j = lower_bound(lines.begin(), lines.end(), array<ll, 4>{a, b, c, d}) - lines.begin() + 1;
        holes[j]++;
    }
    seg.init(pv+1);
    for(int i = 1; i <= pv; i++) {
        holes[i] += holes[i-1];
        seg.update(i, h[i]);
    }
    ld _tm = dnc(1, pv, 0);
    cout << fixed << setprecision(2);
    // cout << _tm << "\n";
    cout << rem << "\n";
}