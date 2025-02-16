#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")


#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 201010;

struct MinSeg {
    ll N;
    vector<ll> tree;
    void init(ll _N)
    {
        N = _N;
        tree.resize(4*N);
    }

    void update(ll x, ll v, ll s, ll e, ll idx)
    {
        if(e < x || x < s) return;
        if(s == e) {
            tree[idx] = v;
            return;
        }
        ll m = (s + e) / 2;
        update(x, v, s, m, 2*idx);
        update(x, v, m+1, e, 2*idx+1);
        tree[idx] = min(tree[2*idx], tree[2*idx+1]);
    }

    ll query(ll l, ll r, ll s, ll e, ll idx)
    {
        if(r < s || e < l) return 1e9;
        if(l <= s && e <= r) return tree[idx];
        ll m = (s + e) / 2;
        return min(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
    }

    void update(ll x, ll v)
    {
        update(x, v, 1, N, 1);
    }

    ll query(ll l, ll r)
    {
        return query(l, r, 1, N, 1);
    }
};

struct Seg {
    ll N;
    vector<ll> tree;
    void init(ll _N)
    {
        N = _N;
        tree.resize(4*N);
    }

    void update(ll x, ll v, ll s, ll e, ll idx)
    {
        if(e < x || x < s) return;
        if(s == e) {
            tree[idx] = max(v, tree[idx]);
            return;
        }
        ll m = (s + e) / 2;
        update(x, v, s, m, 2*idx);
        update(x, v, m+1, e, 2*idx+1);
        tree[idx] = max(tree[2*idx], tree[2*idx+1]);
    }

    ll query(ll l, ll r, ll s, ll e, ll idx)
    {
        if(r < s || e < l) return -1;
        if(l <= s && e <= r) return tree[idx];
        ll m = (s + e) / 2;
        return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
    }

    void update(ll x, ll v)
    {
        update(x, v, 1, N, 1);
    }

    ll query(ll l, ll r)
    {
        return query(l, r, 1, N, 1);
    }
};

struct Line {
	mutable ll m, k, p;
	bool operator<(const Line& o) const { return m < o.m; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	//(for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { //floored division
		return a / b - ((a ^ b) < 0 && a % b != 0);
	}
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->m == y->m) x->p = x->k > y->k ? inf : -inf;
		else x->p = div(y->k - x->k, x->m - y->m);
		return x->p >= y->p;
	}
	void add(ll m, ll k) { //add y = mx + k
		auto z = insert({ m, k, 0 }), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}
	ll query(ll x) {
        if(empty()) return 0;
		auto l = *lower_bound(x);
		return l.m * x + l.k;
	}
};

struct CHTSeg {
    ll N;
    vector<LineContainer> tree;
    void init(ll _N)
    {
        N = _N;
        tree.resize(4*N);
    }

    void update(ll x, ll m, ll k, ll s, ll e, ll idx)
    {
        if(e < x || x < s) return;
        tree[idx].add(m, k);
        if(s == e) {
            return;
        }
        ll mid = (s + e) / 2;
        update(x, m, k, s, mid, 2*idx);
        update(x, m, k, mid+1, e, 2*idx+1);
    }

    ll query(ll l, ll r, ll x, ll s, ll e, ll idx)
    {
        if(r < s || e < l) return -1;
        if(l <= s && e <= r) return tree[idx].query(x);
        ll m = (s + e) / 2;
        return max(query(l, r, x, s, m, 2*idx), query(l, r, x, m+1, e, 2*idx+1));
    }

    void update(ll x, ll m, ll k)
    {
        update(x, m, k, 1, N, 1);
    }

    ll query(ll l, ll r, ll x)
    {
        return query(l, r, x, 1, N, 1);
    }
};

struct Qt {
    ll l, r, idx;
};

ll N, Q;
ll H[MAXN];
ll ans[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(ll i = 1; i <= N; i++) cin >> H[i];
    Q = N;
    vector<Qt> q(Q);
    for(ll i = 0; i < Q; i++) {
        q[i].l = 1;
        q[i].r = i+1;
        q[i].idx = i + 1;
    }

    MinSeg mnsg;
    mnsg.init(N);
    for(ll i = 1; i <= N; i++) mnsg.update(i, H[i]);

    for(auto [l, r, i] : q) {
        ans[i] = mnsg.query(l, r) * (r - l + 1);
    }

    stack<ll> s;
    vector<tuple<ll, ll, ll>> v;
    for(ll i = 1; i <= N+1; i++) {
        while(s.size() && H[i] < H[s.top()]) {
            ll h = H[s.top()]; s.pop();
            ll l = s.empty() ? 1 : s.top() + 1;
            ll w = s.empty() ? i - 1 : i - s.top() - 1;
            v.emplace_back(l, i-1, w*h);
        }
        s.push(i);
    }

    sort(v.begin(), v.end(), greater<>());
    sort(q.begin(), q.end(), [](Qt a, Qt b){
        return a.l > b.l;
    });

    ll idx = 0;
    Seg seg;
    seg.init(N);
    for(auto [l, r, i] : q) {
        while(idx < v.size() && get<0>(v[idx]) >= l) {
            auto [a, b, area] = v[idx];
            seg.update(b, area);
            idx++;
        }
        ans[i] = max(ans[i], seg.query(l, r));
    }

    idx = 0;
    CHTSeg cht;
    cht.init(N);
    for(auto [l, r, i] : q) {
        while(idx < v.size() && get<0>(v[idx]) >= l) {
            auto [a, b, area] = v[idx];
            ll h = area / (b - a + 1);
            cht.update(b, h, -h * (a - 1));
            idx++;
        }
        ans[i] = max(ans[i], cht.query(r, N, r));
    }

    sort(v.begin(), v.end(), [](tuple<ll, ll, ll> a, tuple<ll, ll, ll> b){
        return get<1>(a) < get<1>(b);
    });
    sort(q.begin(), q.end(), [](Qt a, Qt b)
    {
        return a.r < b.r;
    });

    for(ll i = 1; i <= Q; i++) {
        cout << ans[i] << "\n";
    }
}