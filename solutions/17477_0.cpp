#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 505050;
const ll inf = 1e18;

struct Node {
    ll mn, cmn, smn, mx, cmx, smx, cnt;
    ll add, ladd, lmn, lmx;
};

int N, M, A[MAXN];
Node tree[4*MAXN];

void apply_add(int s, int e, int idx, ll add, ll ladd)
{
    tree[idx].mn += add;
    tree[idx].mx += add;
    tree[idx].smn += add;
    tree[idx].smx += add;
    tree[idx].cnt += (e - s + 1) * ladd;
    tree[idx].add += add;
    tree[idx].ladd += ladd;
}

void apply_min(int s, int e, int idx, ll mx, ll lmx)
{
    if(tree[idx].mx <= mx) return;
    if(tree[idx].mx == tree[idx].mn)
        tree[idx].mn = mx;
    else if(tree[idx].mx == tree[idx].smn)
        tree[idx].smn = mx;
    tree[idx].mx = mx;
    tree[idx].lmx += lmx;
    if(tree[idx].mx == tree[idx].mn)
        tree[idx].lmn += lmx;
    tree[idx].cnt += lmx * tree[idx].cmx;
}

void apply_max(int s, int e, int idx, ll mn, ll lmn)
{
    if(tree[idx].mn >= mn) return;
    if(tree[idx].mn == tree[idx].mx) 
        tree[idx].mx = mn;
    else if(tree[idx].mn == tree[idx].smx)
        tree[idx].smx = mn;
    tree[idx].mn = mn;
    tree[idx].lmn += lmn;
    if(tree[idx].mx == tree[idx].mn)
        tree[idx].lmx += lmn;
    tree[idx].cnt += lmn * tree[idx].cmn;
}

void push(int s, int e, int idx)
{
    if(s != e) {
        int m = (s + e) / 2;
        apply_add(s,   m, 2*idx,   tree[idx].add, tree[idx].ladd);
        apply_add(m+1, e, 2*idx+1, tree[idx].add, tree[idx].ladd);
        apply_min(s,   m, 2*idx,   tree[idx].mx, tree[idx].lmx);
        apply_min(m+1, e, 2*idx+1, tree[idx].mx, tree[idx].lmx);
        apply_max(s,   m, 2*idx,   tree[idx].mn, tree[idx].lmn);
        apply_max(m+1, e, 2*idx+1, tree[idx].mn, tree[idx].lmn);
    }
    tree[idx].add = tree[idx].ladd = tree[idx].lmn = tree[idx].lmx = 0;
}

void pull(int s, int e, int idx)
{
    if(tree[2*idx].mn < tree[2*idx+1].mn) {
        tree[idx].mn = tree[2*idx].mn;
        tree[idx].smn = min(tree[2*idx].smn, tree[2*idx+1].mn);
        tree[idx].cmn = tree[2*idx].cmn;
    } else if(tree[2*idx+1].mn < tree[2*idx].mn) {
        tree[idx].mn = tree[2*idx+1].mn;
        tree[idx].smn = min(tree[2*idx+1].smn, tree[2*idx].mn);
        tree[idx].cmn = tree[2*idx+1].cmn;
    } else {
        tree[idx].mn = tree[2*idx].mn;
        tree[idx].smn = min(tree[2*idx].smn, tree[2*idx+1].smn);
        tree[idx].cmn = tree[2*idx].cmn + tree[2*idx+1].cmn;
    }

    if(tree[2*idx].mx > tree[2*idx+1].mx) {
        tree[idx].mx = tree[2*idx].mx;
        tree[idx].smx = max(tree[2*idx].smx, tree[2*idx+1].mx);
        tree[idx].cmx = tree[2*idx].cmx;
    } else if(tree[2*idx+1].mx > tree[2*idx].mx) {
        tree[idx].mx = tree[2*idx+1].mx;
        tree[idx].smx = max(tree[2*idx+1].smx, tree[2*idx].mx);
        tree[idx].cmx = tree[2*idx+1].cmx;
    } else {
        tree[idx].mx = tree[2*idx].mx;
        tree[idx].smx = max(tree[2*idx].smx, tree[2*idx+1].smx);
        tree[idx].cmx = tree[2*idx].cmx + tree[2*idx+1].cmx;
    }

    tree[idx].cnt = tree[2*idx].cnt + tree[2*idx+1].cnt;
}

void init(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx].mn = tree[idx].mx = A[s];
        tree[idx].cmn = tree[idx].cmx = 1;
        tree[idx].smn = inf;
        tree[idx].smx = -inf;
        tree[idx].cnt = tree[idx].add = tree[idx].ladd = tree[idx].lmn = tree[idx].lmx = 0;
        return;
    }
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    pull(s, e, idx);
}

void upadd(int l, int r, ll v, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        apply_add(s, e, idx, v, 1);
        return;
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    upadd(l, r, v, s, m, 2*idx);
    upadd(l, r, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}

void upmin(int l, int r, ll v, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        if(tree[idx].mx <= v) return;
        if(tree[idx].smx < v) {
            apply_min(s, e, idx, v, 1);
            return;
        }
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    upmin(l, r, v, s, m, 2*idx);
    upmin(l, r, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}

void upmax(int l, int r, ll v, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        if(tree[idx].mn >= v) return;
        if(tree[idx].smn > v) {
            apply_max(s, e, idx, v, 1);
            return;
        }
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    upmax(l, r, v, s, m, 2*idx);
    upmax(l, r, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}

ll query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx].cnt;
    int m = (s + e) / 2;
    push(s, e, idx);
    return query(l, r, s, m, 2*idx) + query(l, r, m+1, e, 2*idx+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    init();

    cin >> M;
    while(M--) {
        int t, l, r;
        cin >> t >> l >> r;
        if(t == 1) {
            ll x; cin >> x;
            if(x != 0) upadd(l, r, x);
        } else if(t == 2) {
            ll y; cin >> y;
            upmax(l, r, y);
        } else if(t == 3) {
            ll y; cin >> y;
            upmin(l, r, y);
        } else {
            ll ans = query(l, r);
            cout << ans << "\n";
        }
    }
}