#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100010;

struct Q2 {
    ll k, s, t, idx;
};

struct T {
    ll lmx, rmx, mx, s;
};

ll N, M, Q, ans[MAXN];
T tree[4*MAXN];
vector<tuple<ll, ll>> updates[MAXN];

T merge(T a, T b)
{
    T ret = {};
    ret.lmx = max(a.lmx, a.s + b.lmx);
    ret.rmx = max(b.rmx, b.s + a.rmx);
    ret.mx = max({ret.lmx, ret.rmx, a.rmx + b.lmx, a.mx, b.mx});
    ret.s = a.s + b.s;
    return ret;
}

void upd(ll x, ll v, ll s = 1, ll e = M, ll idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx].mx = tree[idx].lmx = tree[idx].rmx = tree[idx].s = v;
        return;
    }

    ll m = (s + e) / 2;
    upd(x, v, s, m, 2*idx);
    upd(x, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T qry(ll l, ll r, ll s = 1, ll e = M, ll idx = 1)
{
    if(l <= s && e <= r) return tree[idx];
    ll m = (s + e) / 2;
    if(r <= m) return qry(l, r, s, m, 2*idx);
    if(m+1 <= l) return qry(l, r, m+1, e, 2*idx+1);
    return merge(qry(l, r, s, m, 2*idx), qry(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;

    for(ll i = 1; i <= M; i++) {
        ll l, r, x;
        cin >> l >> r >> x;
        updates[l].emplace_back(i, x);
        updates[r+1].emplace_back(i, 0);
    }

    cin >> Q;
    vector<Q2> q2(Q);
    for(ll i = 0; i < Q; i++) {
        cin >> q2[i].k >> q2[i].s >> q2[i].t;
        q2[i].idx = i+1;
    }
    sort(q2.begin(), q2.end(), [](Q2 a, Q2 b) {
        return a.k < b.k;
    });

    ll j = 0;
    for(ll i = 1; i <= N; i++) {
        for(auto [idx, v] : updates[i]) upd(idx, v);
        while(j < Q && q2[j].k == i) {
            ans[q2[j].idx] = qry(q2[j].s, q2[j].t).mx;
            j++;
        }
    }

    for(ll i = 1; i <= Q; i++) cout << ans[i] << "\n";
}