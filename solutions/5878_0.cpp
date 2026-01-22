#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

struct Node {
    ll dp, m, mn, mx;
};

ll N, L, H[MAXN], W[MAXN], lazy[4*MAXN];
Node tree[4*MAXN];

Node merge(Node a, Node b)
{
    if(a.dp + a.m < b.dp + b.m) return {a.dp, a.m, min(a.mn, b.mn), max(a.mx, b.mx)};
    else return {b.dp, b.m, min(a.mn, b.mn), max(a.mx, b.mx)};
}

void push(int s, int e, int idx)
{
    if(lazy[idx] == -1) return;
    tree[idx].m = lazy[idx];
    tree[idx].mn = lazy[idx];
    tree[idx].mx = lazy[idx];
    if(s != e) {
        lazy[2*idx] = lazy[2*idx+1] = lazy[idx];
    }
    lazy[idx] = -1;
}

void point_update(int x, ll v, int s = 0, int e = N, int idx = 1)
{
    push(s, e, idx);
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx].dp = v;
        return;
    }
    int m = (s + e) / 2;
    point_update(x, v, s, m, 2*idx);
    point_update(x, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void range_update(int l, int r, ll v, int s = 0, int e = N, int idx = 1)
{
    push(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        if(v < tree[idx].mn) return;
        if(tree[idx].mn == tree[idx].mx) {
            lazy[idx] = v;
            push(s, e, idx);
            return;
        }
    }
    int m = (s + e) / 2;
    range_update(l, r, v, s, m, 2*idx);
    range_update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

Node query(int l, int r, int s = 0, int e = N, int idx = 1)
{
    push(s, e, idx);
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    if(r <= m) return query(l, r, s, m, 2*idx);
    if(m+1 <= l) return query(l, r, m+1, e, 2*idx+1);
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> L;
    for(int i = 1; i <= N; i++) cin >> H[i] >> W[i];

    memset(lazy, -1, sizeof(lazy));

    int j = 0;
    ll width = 0;
    for(int i = 1; i <= N; i++) {
        range_update(0, i-1, H[i]);
        width += W[i];
        while(width > L) {
            width -= W[j++];
        }
        auto mn = query(j-1, i-1);
        ll dp = mn.dp + mn.m;
        point_update(i, dp);
    }

    cout << query(N, N).dp << "\n";
}