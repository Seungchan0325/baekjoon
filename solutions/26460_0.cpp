#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;
const ll inf = 1e18;

struct Line {
    ll a, b;
    Line(ll _a = 0, ll _b = 0) : a(_a), b(_b) {}
    ll eval(ll x) const { return a * x + b; }

    void shift(ll t)
    {
        b += a * t;
        a = 0;
    }
    
    Line operator + (const Line& rhs) const {
        return Line(a+rhs.a, b+rhs.b);
    }
};

struct Node {
    ll mn, smn;
    Line lmx, rmx, mx, all;
    ll melt;
};

ll intersect(const Line& a, const Line& b, ll t)
{
    if(a.a == b.a) return inf;
    ll p = b.b - a.b;
    ll q = a.a - b.a;
    if(q < 0) p = -p, q = -q;
    ll ret = p >= 0 ? (p + q - 1) / q : -((-p)/q);
    if(ret <= t) return inf;
    return ret;
}

Line argmax(initializer_list<Line> lines, ll t)
{
    return *ranges::max_element(lines, {}, [t](const Line& l){ return pair(l.eval(t), l.a); });
}

Node merge(Node a, Node b)
{
    Node res;
    if(a.mn < b.mn) {
        res.mn = a.mn;
        res.smn = min(a.smn, b.mn);
        res.melt = a.melt;
        b.lmx.shift(b.mn);
        b.rmx.shift(b.mn);
        b.mx.shift(b.mn);
        b.all.shift(b.mn);
    } else if(a.mn > b.mn) {
        res.mn = b.mn;
        res.smn = min(b.smn, a.mn);
        res.melt = b.melt;
        a.lmx.shift(a.mn);
        a.rmx.shift(a.mn);
        a.mx.shift(a.mn);
        a.all.shift(a.mn);
    } else {
        res.mn = a.mn;
        res.smn = min(a.smn, b.smn);
        res.melt = min(a.melt, b.melt);
    }
    ll t = res.mn;
    res.lmx = argmax({a.lmx, a.all+b.lmx}, t);
    res.melt = min(intersect(a.lmx, a.all+b.lmx, t), res.melt);
    res.rmx = argmax({b.rmx, b.all+a.rmx}, t);
    res.melt = min(intersect(b.rmx, b.all+a.rmx, t), res.melt);
    res.mx = argmax({a.mx, b.mx, a.rmx+b.lmx}, t);
    res.melt = min(intersect(a.mx, b.mx, t), res.melt);
    res.melt = min(intersect(a.rmx+b.lmx, b.mx, t), res.melt);
    res.melt = min(intersect(a.mx, a.rmx+b.lmx, t), res.melt);
    res.all = a.all+b.all;
    return res;
}

int N, Q, A[MAXN];
Node tree[4*MAXN];

void apply(int s, int e, int idx, ll v)
{
    tree[idx].mn = v;
}

void push(int s, int e, int idx)
{
    if(s != e) {
        int m = (s + e) / 2;
        if(tree[2*idx].mn < tree[idx].mn) apply(s, m, 2*idx, tree[idx].mn);
        if(tree[2*idx+1].mn < tree[idx].mn) apply(m+1, e, 2*idx+1, tree[idx].mn);
    }
}

void pull(int s, int e, int idx)
{
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void init(int s=1, int e=N, int idx=1)
{
    if(s == e) {
        tree[idx].mn = A[s];
        tree[idx].smn = inf;
        tree[idx].lmx = tree[idx].rmx = tree[idx].mx = tree[idx].all = Line(1, 0);
        tree[idx].melt = inf;
        return;
    }
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    pull(s, e, idx);
}

void heaten(int s=1, int e=N, int idx=1)
{
    if(tree[idx].melt > tree[idx].mn) return;
    if(s == e) return;
    int m = (s + e) / 2;
    push(s, e, idx);
    heaten(s, m, 2*idx);
    heaten(m+1, e, 2*idx+1);
    pull(s, e, idx);
}

void update(int l, int r, ll v, int s=1, int e=N, int idx=1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        if(v <= tree[idx].mn) return;
        if(v < tree[idx].smn) {
            apply(s, e, idx, v);
            heaten(s, e, idx);
            return;
        }
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}

Node query(int l, int r, int s=1, int e=N, int idx=1)
{
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    push(s, e, idx);
    if(r <= m) return query(l, r, s, m, 2*idx);
    if(m+1 <= l) return query(l, r, m+1, e, 2*idx+1);
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

void force(int s = 1, int e = N, int idx = 1)
{
    if(s == e) return;
    int m = (s + e) / 2;
    push(s, e, idx);
    force(s, m, 2*idx);
    force(m+1, e, 2*idx+1);
    pull(s, e, idx);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for(int i = 1; i <= N; i++) cin >> A[i];
    init();
    while(Q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if(t == 0) {
            int x;
            cin >> x;
            update(l, r, x);
        } else {
            Node t = query(l, r);
            ll ans = max<ll>(t.mx.eval(t.mn), 0);
            cout << ans << "\n";
        }
    }
}