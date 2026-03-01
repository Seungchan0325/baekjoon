#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 505050;
const ll inf = 1e18;

struct Node {
    ll mn, cmn, smn, mx, cmx, smx, sum, lzadd;
};

int N, M, A[MAXN];
Node tree[4*MAXN];

void apply_add(int s, int e, int idx, ll v)
{
    tree[idx].mn += v;
    tree[idx].mx += v;
    tree[idx].smn += v;
    tree[idx].smx += v;
    tree[idx].sum += (e - s + 1) * v;
    tree[idx].lzadd += v;
}

void apply_min(int s, int e, int idx, ll mx)
{
    if(tree[idx].mx <= mx) return;
    if(tree[idx].mx == tree[idx].mn)
        tree[idx].mn = mx;
    else if(tree[idx].mx == tree[idx].smn)
        tree[idx].smn = mx;
    tree[idx].sum += tree[idx].cmx * (mx-tree[idx].mx);
    tree[idx].mx = mx;
}

void apply_max(int s, int e, int idx, ll mn)
{
    if(tree[idx].mn >= mn) return;
    if(tree[idx].mn == tree[idx].mx) 
        tree[idx].mx = mn;
    else if(tree[idx].mn == tree[idx].smx)
        tree[idx].smx = mn;
    tree[idx].sum += tree[idx].cmn * (mn-tree[idx].mn);
    tree[idx].mn = mn;
}

void push(int s, int e, int idx)
{
    if(s != e) {
        int m = (s + e) / 2;
        apply_add(s,   m, 2*idx,   tree[idx].lzadd);
        apply_add(m+1, e, 2*idx+1, tree[idx].lzadd);
        apply_min(s,   m, 2*idx,   tree[idx].mx);
        apply_min(m+1, e, 2*idx+1, tree[idx].mx);
        apply_max(s,   m, 2*idx,   tree[idx].mn);
        apply_max(m+1, e, 2*idx+1, tree[idx].mn);
    }
    tree[idx].lzadd = 0;
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

    tree[idx].sum = tree[2*idx].sum + tree[2*idx+1].sum;
}

void init(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx].mn = tree[idx].mx = tree[idx].sum = A[s];
        tree[idx].cmn = tree[idx].cmx = 1;
        tree[idx].smn = inf;
        tree[idx].smx = -inf;
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
        apply_add(s, e, idx, v);
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
            apply_min(s, e, idx, v);
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
            apply_max(s, e, idx, v);
            return;
        }
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    upmax(l, r, v, s, m, 2*idx);
    upmax(l, r, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}

ll Qmin(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return inf;
    if(l <= s && e <= r) return tree[idx].mn;
    int m = (s + e) / 2;
    push(s, e, idx);
    return min(Qmin(l, r, s, m, 2*idx), Qmin(l, r, m+1, e, 2*idx+1));
}

ll Qmax(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return -inf;
    if(l <= s && e <= r) return tree[idx].mx;
    int m = (s + e) / 2;
    push(s, e, idx);
    return max(Qmax(l, r, s, m, 2*idx), Qmax(l, r, m+1, e, 2*idx+1));
}

ll Qsum(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx].sum;
    int m = (s + e) / 2;
    push(s, e, idx);
    return Qsum(l, r, s, m, 2*idx) + Qsum(l, r, m+1, e, 2*idx+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    init();

    cin >> M;
    while(M--) {
        int t, l, r, x;
        cin >> t >> l >> r;
        if(1 <= t && t <= 3) cin >> x;
        if(t == 1) {
            upmin(l, r, x);
        } else if(t == 2) {
            upmax(l, r, x);
        } else if(t == 3) {
            upadd(l, r, x);
        } else if(t == 4) {
            cout << Qmin(l, r) << "\n";
        } else if(t == 5) {
            cout << Qmax(l, r) << "\n";
        } else if(t == 6) {
            cout << Qsum(l, r) << "\n";
        }
    }
}