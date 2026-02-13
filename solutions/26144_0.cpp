#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1010101;

const ll inf = 1e18;

struct Line {
    ll a, b;
    ll get(ll x) { return a * x + b; }
};

ll intersect(const Line& a, const Line& b)
{
    if(a.a == b.a) return inf;
    ll p = a.b - b.b;
    ll q = b.a - a.a;
    if(q < 0) p = -p, q = -q;
    ll res = (p + q - 1) / q;
    return res;
}

struct Node {
    ll t;
    ll melt;
    ll lazyb;
    ll lazyt;
    Line x;
    ll eval() { return x.get(t); }
};

struct KST {
private:
    int n;
    vector<Node> tree;
public:
    void init(int _n) {
        n = _n;
        tree.resize(4*n);
        init(0, n-1, 1);
    }
    void heaten(int l, int r, ll dt)
    {
        heaten(l, r, dt, 0, n-1, 1);
    }
    void update(int l, int r, ll v)
    {
        update(l, r, v, 0, n-1, 1);
    }
    void update(int x, Line v)
    {
        update(x, v, 0, n-1, 1);
    }
    ll query(int l, int r)
    {
        return query(l, r, 0, n-1, 1);
    }
    int query()
    {
        return query(0, n-1, 1);
    }
private:
    void apply(int s, int e, int idx, ll t, ll v)
    {
        if(tree[idx].melt < inf)
            tree[idx].melt = max<ll>(0, tree[idx].melt-t);
        tree[idx].t += t;
        tree[idx].lazyt += t;
        tree[idx].x.b += v;
        tree[idx].lazyb += v;
    }

    void push(int s, int e, int idx)
    {
        if(s != e) {
            int m = (s + e) / 2;
            apply(s, m, 2*idx, tree[idx].lazyt, tree[idx].lazyb);
            apply(m+1, e, 2*idx+1, tree[idx].lazyt, tree[idx].lazyb);
        }
        tree[idx].lazyt = 0;
        tree[idx].lazyb = 0;
    }

    void pull(int s, int e, int idx)
    {
        if(tree[2*idx].eval() > tree[2*idx+1].eval()) {
            tree[idx].x = tree[2*idx].x;
            tree[idx].t = tree[2*idx].t;
        } else {
            tree[idx].x = tree[2*idx+1].x;
            tree[idx].t = tree[2*idx+1].t;
        }
        tree[idx].melt = min(tree[2*idx].melt, tree[2*idx+1].melt);
        Line l = tree[2*idx].x; l.b += tree[2*idx].t * l.a;
        Line r = tree[2*idx+1].x; r.b += tree[2*idx+1].t * r.a;
        ll mt = intersect(l, r);
        if(mt > 0) tree[idx].melt = min(tree[idx].melt, mt);
    }

    void init(int s, int e, int idx)
    {
        tree[idx].lazyb = tree[idx].lazyt = 0;
        if(s == e) {
            tree[idx].x = {0, -inf};
            tree[idx].t = 0;
            tree[idx].melt = inf;
            return;
        }
        int m = (s + e) / 2;
        init(s, m, 2*idx);
        init(m+1, e, 2*idx+1);
        pull(s, e, idx);
    }

    void heaten(int l, int r, ll dt, int s, int e, int idx)
    {
        if(e < l || r < s) return;
        if(l <= s && e <= r) {
            if(tree[idx].melt > dt) {
                apply(s, e, idx, dt, 0);
                return;
            }
        }
        push(s, e, idx);
        int m = (s + e) / 2;
        heaten(l, r, dt, s, m, 2*idx);
        heaten(l, r, dt, m+1, e, 2*idx+1);
        pull(s, e, idx);
    }

    void update(int x, Line v, int s, int e, int idx)
    {
        if(e < x || x < s) return;
        if(s == e) {
            tree[idx].x = v;
            return;
        }
        push(s, e, idx);
        int m = (s + e) / 2;
        if(x <= m) update(x, v, s, m, 2*idx);
        else update(x, v, m+1, e, 2*idx+1);
        pull(s, e, idx);
    }

    void update(int l, int r, ll v, int s, int e, int idx)
    {
        if(e < l || r < s) return;
        if(l <= s && e <= r) {
            apply(s, e, idx, 0, v);
            return;
        }
        push(s, e, idx);
        int m = (s + e) / 2;
        update(l, r, v, s, m, 2*idx);
        update(l, r, v, m+1, e, 2*idx+1);
        pull(s, e, idx);
    }

    ll query(int l, int r, int s, int e, int idx)
    {
        if(e < l || r < s) return -inf;
        if(l <= s && e <= r) return tree[idx].eval();
        push(s, e, idx);
        int m = (s + e) / 2;
        return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
    }

    int query(int s, int e, int idx)
    {
        if(s == e) return s;
        int m = (s + e) / 2;
        push(s, e, idx);
        if(tree[idx].eval() == tree[2*idx].eval()) return query(s, m, 2*idx);
        if(tree[idx].eval() == tree[2*idx+1].eval()) return query(m+1, e, 2*idx+1);
        assert(0);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N;
    cin >> N;
    vector<pair<ll, ll>> v(N);
    for(auto& [d, h] : v) cin >> d >> h;
    sort(v.begin(), v.end());
    KST kst; kst.init(N);
    for(int i = 0; i < N; i++) {
        auto [d, h] = v[i];
        kst.update(i, {d, h});
    }
    ll ans = 0;
    for(int i = 1; i <= N; i++) {
        ans += kst.query(0, N-1);
        cout << ans << "\n";
        int j = kst.query();
        kst.update(j, {0, -inf});
        kst.heaten(j+1, N-1, 1);
        kst.update(0, j-1, v[j].first);
    }
}