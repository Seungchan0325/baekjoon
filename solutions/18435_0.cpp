#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 200005;

struct Q_t {
    ll T, L, R, idx;
};

struct lazy_seg {
    ll n;
    vector<ll> tree, lazy;

    lazy_seg(ll n) : n(n), tree(4*n), lazy(4*n) {}

    void propagate(ll s, ll e, ll idx)
    {
        if(lazy[idx]) {
            tree[idx] += (e - s + 1) * lazy[idx];
            if(s != e) {
                lazy[2*idx] += lazy[idx];
                lazy[2*idx+1] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }

    void _upd(ll l, ll r, ll delta, ll s, ll e, ll idx)
    {
        propagate(s, e, idx);

        if(e < l || r < s) return;

        if(l <= s && e <= r) {
            lazy[idx] += delta;
            propagate(s, e, idx);
            return;
        }

        ll m = (s + e) / 2;
        _upd(l, r, delta, s, m, 2*idx);
        _upd(l, r, delta, m+1, e, 2*idx+1);
        tree[idx] = tree[2*idx] + tree[2*idx+1];
    }

    ll _qry(ll l, ll r, ll s, ll e, ll idx)
    {
        propagate(s, e, idx);
        if(e < l || r < s) return 0;

        if(l <= s && e <= r) return tree[idx];

        ll m = (s + e) / 2;
        return _qry(l, r, s, m, 2*idx) + _qry(l, r, m+1, e, 2*idx+1);
    }

    void upd(ll l, ll r, ll delta)
    {
        _upd(l, r, delta, 1, n, 1);
    }

    ll qry(ll l, ll r)
    {
        return _qry(l, r, 1, n, 1);
    }
};

ll N, Q, S[MAXN], L[MAXN], R[MAXN];
ll ans[MAXN];
Q_t qrys[MAXN];

int main()
{
    cin >> N >> Q;
    for(ll i = 1; i <= N; i++) cin >> S[i];
    for(ll i = 0; i < Q; i++) {
        cin >> qrys[i].T >> qrys[i].L >> qrys[i].R;
        qrys[i].idx = i;
    }

    sort(qrys, qrys + Q, [](Q_t a, Q_t b){
        return a.T < b.T;
    });

    stack<ll> s;
    for(ll i = 1; i <= N; i++) {
        while(s.size() && S[s.top()] < S[i]) {
            R[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    while(s.size()) {
        R[s.top()] = N+1;
        s.pop();
    }
    for(ll i = N; i >= 1; i--) {
        while(s.size() && S[s.top()] <= S[i]) {
            L[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    while(s.size()) {
        L[s.top()] = -1;
        s.pop();
    }

    lazy_seg seg1(2*N+5), seg2(N+5);
    vector<tuple<ll, ll, ll, ll>> upd1, upd2;
    auto add_tri = [&](ll t, ll l, ll r, ll v)
    {
        if(l > r) return;
        upd1.emplace_back(t, l+N, N+N, v);
        upd1.emplace_back(t+r-l+1, l+N, N+N, -v);
        if(r+1 <= N) {
            upd2.emplace_back(t, r+1, N, -v);
            upd2.emplace_back(t+r-l+1, r+1, N, v);
        }
    };
    for(ll i = 1; i <= N; i++) {
        if(L[i] != -1) {
            add_tri(0, L[i]+1, i-1, -S[i]);
            add_tri(0, L[i]+1, R[i]-1, S[i]);
            add_tri(0, i+1, R[i]-1, -S[i]);
        } else {
            upd2.emplace_back(0, i, R[i]-1, S[i]);
            add_tri(0, i+1, R[i]-1, -S[i]);
        }
    }

    sort(upd1.begin(), upd1.end());
    sort(upd2.begin(), upd2.end());

    ll l1 = 0;
    ll l2 = 0;
    for(ll i = 0; i < Q; i++) {
        while(l1 < upd1.size() && get<0>(upd1[l1]) <= qrys[i].T) {
            auto [t, l, r, v] = upd1[l1++];
            seg1.upd(l, r, v);
        }
        while(l2 < upd2.size() && get<0>(upd2[l2]) <= qrys[i].T) {
            auto [t, l, r, v] = upd2[l2++];
            seg2.upd(l, r, v);
        }

        ll t = qrys[i].T;
        ll l = qrys[i].L;
        ll r = qrys[i].R;
        ll result = seg1.qry(l+N-t, r+N-t) + seg2.qry(l, r);
        ans[qrys[i].idx] = result;
    }
    for(ll i = 0; i < Q; i++) {
        cout << ans[i] << "\n";
    }
}