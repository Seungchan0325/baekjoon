#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

const int MAXN = 303030;
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

bool chk[MAXN];
ll N, K, h[MAXN], lef[MAXN], rig[MAXN], pv, par[MAXN], w[MAXN], in[MAXN], out[MAXN], rin[MAXN], t;
ll tree[4*MAXN], lazy[4*MAXN];
SegTree seg;

void push(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] += lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, ll v, int s = 1, int e = pv, int idx = 1)
{
    push(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        lazy[idx] += v;
        push(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int query(int s = 1, int e = pv, int idx = 1)
{
    push(s, e, idx);
    if(s == e) return s;
    int m = (s + e) / 2;
    push(s, m, 2*idx); push(m+1, e, 2*idx+1);
    if(tree[2*idx] >= tree[2*idx+1]) return query(s, m, 2*idx);
    else return query(m+1, e, 2*idx+1);
}

void dnc(int l, int r, int ph, int p)
{
    if(r < l) return;
    int m = seg.query(l, r).second;
    in[m] = ++t;
    rin[in[m]] = m;
    par[m] = p;
    w[m] = (rig[r] - lef[l]) * (h[m] - ph);
    dnc(l, m-1, h[m], m);
    dnc(m+1, r, h[m], m);
    out[m] = t;
}

int main()
{
    cin >> N;
    ll x, y;
    x = y = 0;
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
            x = nx;
        }
    }
    cin >> K;
    seg.init(pv+1);
    for(int i = 1; i <= pv; i++) {
        seg.update(i, h[i]);
    }
    dnc(1, pv, 0, -1);

    for(int i = 1; i <= pv; i++) {
        update(in[i], out[i], w[i]);
    }
    ll ans = 0;
    for(int i = 0; i < K; i++) {
        ans += tree[1];
        int j = rin[query()];
        while(j != -1 && !chk[j]) {
            update(in[j], out[j], -w[j]);
            chk[j] = true;
            j = par[j];
        }
    }
    cout << ans << "\n";
}