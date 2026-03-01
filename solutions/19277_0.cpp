#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

struct Node {
    int mn, mx, lzset, lzadd;
};

int N, Q, A[MAXN];
Node tree[4*MAXN];

void apply_set(int s, int e, int idx, int v)
{
    if(v != -1) {
        tree[idx].mn = tree[idx].mx = v;
        tree[idx].lzset = v;
        tree[idx].lzadd = 0;
    }
}
void apply_add(int s, int e, int idx, int v)
{
    tree[idx].mn += v;
    tree[idx].mx += v;
    tree[idx].lzadd += v;
}
void push(int s, int e, int idx)
{
    if(s != e) {
        int m = (s + e) / 2;
        apply_set(s, m, 2*idx, tree[idx].lzset);
        apply_set(m+1, e, 2*idx+1, tree[idx].lzset);
        apply_add(s, m, 2*idx, tree[idx].lzadd);
        apply_add(m+1, e, 2*idx+1, tree[idx].lzadd);
    }
    tree[idx].lzset = -1;
    tree[idx].lzadd = 0;
}
void pull(int s, int e, int idx)
{
    tree[idx].mn = min(tree[2*idx].mn, tree[2*idx+1].mn);
    tree[idx].mx = max(tree[2*idx].mx, tree[2*idx+1].mx);
}
void init(int s = 0, int e = N-1, int idx = 1)
{
    tree[idx].lzset = -1;
    tree[idx].lzadd = 0;
    if(s == e) {
        tree[idx].mn = tree[idx].mx = A[s];
        return;
    }
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    pull(s, e, idx);
}
void update_div(int l, int r, int x, int s = 0, int e = N-1, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        if(tree[idx].mn / x == tree[idx].mx / x) {
            apply_set(s, e, idx, tree[idx].mn / x);
            return;
        }
        if(tree[idx].mn + 1 == tree[idx].mx) {
            apply_add(s, e, idx, tree[idx].mn / x - tree[idx].mn);
            return;
        }
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    update_div(l, r, x, s, m, 2*idx);
    update_div(l, r, x, m+1, e, 2*idx+1);
    pull(s, e, idx);
}
void update_add(int l, int r, int x, int s = 0, int e = N-1, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        apply_add(s, e, idx, x);
        return;
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    update_add(l, r, x, s, m, 2*idx);
    update_add(l, r, x, m+1, e, 2*idx+1);
    pull(s, e, idx);
}
int query(int l, int r, int s = 0, int e = N-1, int idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx].mx;
    int m = (s + e) / 2;
    push(s, e, idx);
    return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for(int i = 0; i < N; i++) cin >> A[i];
    init();
    for(int i = 0; i < Q; i++) {
        int t, l, r, x;
        cin >> t >> l >> r >> x;
        if(t == 0) {
            update_add(l, r, x);
        } else if(t == 1) {
            if(x != 1) update_div(l, r, x);
        } else {
            int ans = query(l, r);
            cout << ans << "\n";
        }
    }
}