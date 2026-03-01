#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;
const ll inf = 1e18;

struct Node {
    ll mn, mx, sum, lzset, lzadd;
    bool haslzset;
};

int N, Q, A[MAXN];
Node tree[4*MAXN];

ll fdiv(ll p, ll q) {
    ll r = p / q;
    if (p < 0 && p % q) --r;
    return r;
}
void apply_set(int s, int e, int idx, ll v)
{
    tree[idx].mn = tree[idx].mx = v;
    tree[idx].sum = (e - s + 1) * v;
    tree[idx].haslzset = true;
    tree[idx].lzset = v;
    tree[idx].lzadd = 0;
}
void apply_add(int s, int e, int idx, ll v)
{
    tree[idx].mn += v;
    tree[idx].mx += v;
    tree[idx].sum += (e - s + 1) * v;
    tree[idx].lzadd += v;
}
void push(int s, int e, int idx)
{
    if(s != e) {
        int m = (s + e) / 2;
        if(tree[idx].haslzset) {
            apply_set(s, m, 2*idx, tree[idx].lzset);
            apply_set(m+1, e, 2*idx+1, tree[idx].lzset);
        }
        apply_add(s, m, 2*idx, tree[idx].lzadd);
        apply_add(m+1, e, 2*idx+1, tree[idx].lzadd);
    }
    tree[idx].lzset = 0;
    tree[idx].haslzset = false;
    tree[idx].lzadd = 0;
}
void pull(int s, int e, int idx)
{
    tree[idx].mn = min(tree[2*idx].mn, tree[2*idx+1].mn);
    tree[idx].mx = max(tree[2*idx].mx, tree[2*idx+1].mx);
    tree[idx].sum = tree[2*idx].sum + tree[2*idx+1].sum;
}
void init(int s = 0, int e = N-1, int idx = 1)
{
    tree[idx].lzset = 0;
    tree[idx].haslzset = false;
    tree[idx].lzadd = 0;
    if(s == e) {
        tree[idx].mn = tree[idx].mx = tree[idx].sum = A[s];
        return;
    }
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    pull(s, e, idx);
}
void div(int l, int r, ll x, int s = 0, int e = N-1, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        if(fdiv(tree[idx].mn, x) == fdiv(tree[idx].mx, x)) {
            apply_set(s, e, idx, fdiv(tree[idx].mn, x));
            return;
        }
        if(tree[idx].mn + 1 == tree[idx].mx) {
            apply_add(s, e, idx, fdiv(tree[idx].mn, x) - tree[idx].mn);
            return;
        }
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    div(l, r, x, s, m, 2*idx);
    div(l, r, x, m+1, e, 2*idx+1);
    pull(s, e, idx);
}
void add(int l, int r, ll x, int s = 0, int e = N-1, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        apply_add(s, e, idx, x);
        return;
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    add(l, r, x, s, m, 2*idx);
    add(l, r, x, m+1, e, 2*idx+1);
    pull(s, e, idx);
}
ll Qmin(int l, int r, int s = 0, int e = N-1, int idx = 1)
{
    if(e < l || r < s) return inf;
    if(l <= s && e <= r) return tree[idx].mn;
    int m = (s + e) / 2;
    push(s, e, idx);
    return min(Qmin(l, r, s, m, 2*idx), Qmin(l, r, m+1, e, 2*idx+1));
}
ll Qadd(int l, int r, int s = 0, int e = N-1, int idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx].sum;
    int m = (s + e) / 2;
    push(s, e, idx);
    return Qadd(l, r, s, m, 2*idx) + Qadd(l, r, m+1, e, 2*idx+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for(int i = 0; i < N; i++) cin >> A[i];
    init();
    for(int i = 0; i < Q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if(t == 1) {
            int c; cin >> c;
            add(l, r, c);
        } else if(t == 2) {
            int d; cin >> d;
            if(d != 1) div(l, r, d);
        } else if(t == 3) {
            ll ans = Qmin(l, r);
            cout << ans << "\n";
        } else if(t == 4) {
            ll ans = Qadd(l, r);
            cout << ans << "\n";
        }
    }
}