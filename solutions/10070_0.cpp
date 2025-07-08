#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2020202;

int n, k;

struct Node {
    int mn, mx;
};

Node tree[4*MAXN];
int lazy[4*MAXN];
Node merge(Node a, Node b)
{
    return Node(min(a.mn, b.mn), max(a.mx, b.mx));
}
void push(int s, int e, int idx)
{
    if(lazy[idx] != -1) {
        tree[idx].mn = tree[idx].mx = lazy[idx];
        if(s != e) {
            lazy[2*idx] = lazy[2*idx+1] = lazy[idx];
        }
        lazy[idx] = -1;
    }
}
void update1(int l, int r, int v, int s = 0, int e = n-1, int idx = 1)
{
    push(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        if(tree[idx].mn >= v) return;
        if(tree[idx].mx <= v) {
            lazy[idx] = v;
            push(s, e, idx);
            return;
        }
    }
    int m = (s + e) / 2;
    update1(l, r, v, s, m, 2*idx);
    update1(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}
void update2(int l, int r, int v, int s = 0, int e = n-1, int idx = 1)
{
    push(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        if(tree[idx].mx <= v) return;
        if(tree[idx].mn >= v) {
            lazy[idx] = v;
            push(s, e, idx);
            return;
        }
    }
    int m = (s + e) / 2;
    update2(l, r, v, s, m, 2*idx);
    update2(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}
int query(int x, int s = 0, int e = n-1, int idx = 1)
{
    push(s, e, idx);
    int m = (s + e) / 2;
    if(s == e) return tree[idx].mn;
    if(x <= m) return query(x, s, m, 2*idx);
    if(m+1 <= x) return query(x, m+1, e, 2*idx+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    memset(lazy, -1, sizeof(lazy));
    cin >> n >> k;
    while(k--) {
        int op, l, r, h;
        cin >> op >> l >> r >> h;
        if(op == 1) update1(l, r, h);
        else update2(l, r, h);
    }
    for(int i = 0; i < n; i++) cout << query(i) << "\n";
}