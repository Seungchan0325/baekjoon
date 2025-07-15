#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010101;
const int inf = 1e9;

struct Node {
    int lmn, lmx;
    int rmn, rmx;
    int sum;
    Node(int v = 0) : lmn(min(v, 0)), lmx(max(v, 0)), rmn(min(v, 0)), rmx(max(v, 0)), sum(v) {}
    void inv()
    {
        swap(lmn, lmx);
        swap(rmn, rmx);
        lmn = -lmn;
        lmx = -lmx;
        rmn = -rmn;
        rmx = -rmx;
        sum = -sum;
    }
};

Node merge(Node a, Node b)
{
    Node ret;
    ret.lmn = min(a.lmn, a.sum + b.lmn);
    ret.lmx = max(a.lmx, a.sum + b.lmx);
    ret.rmn = min(b.rmn, b.sum + a.rmn);
    ret.rmx = max(b.rmx, b.sum + a.rmx);
    ret.sum = a.sum + b.sum;
    return ret;
}

struct LazySegTree {
    int n;
    vector<int> lazy;
    vector<Node> tree;
    LazySegTree(int _n)
    {
        n = _n;
        lazy.resize(4*n);
        tree.resize(4*n);
    }
    void push(int s, int e, int idx)
    {
        if(lazy[idx]) {
            tree[idx].inv();
            if(s != e) {
                lazy[2*idx] ^= lazy[idx];
                lazy[2*idx+1] ^= lazy[idx];
            }
            lazy[idx] = 0;
        }
    }

    void update_point(int x, int v, int s, int e, int idx)
    {
        push(s, e, idx);
        if(e < x || x < s) return;
        if(s == e) {
            tree[idx] = v;
            return;
        }
        int m = (s + e) / 2;
        update_point(x, v, s, m, 2*idx);
        update_point(x, v, m+1, e, 2*idx+1);
        tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
    }
    
    void update(int l, int r, int s, int e, int idx)
    {
        push(s, e, idx);
        if(e < l || r < s) return;
        if(l <= s && e <= r) {
            lazy[idx] = 1;
            push(s, e, idx);
            return;
        }
        int m = (s + e) / 2;
        update(l, r, s, m, 2*idx);
        update(l, r, m+1, e, 2*idx+1);
        tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
    }
    
    Node query(int l, int r, int s, int e, int idx)
    {
        push(s, e, idx);
        if(l <= s && e <= r) return tree[idx];
        int m = (s + e) / 2;
        if(r <= m) return query(l, r, s, m, 2*idx);
        if(m+1 <= l) return query(l, r, m+1, e, 2*idx+1);
        return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
    }

    void update_point(int l, int v)
    {
        return update_point(l, v, 1, n, 1);
    }
    void update(int l, int r)
    {
        return update(l, r, 1, n, 1);
    }
    Node query(int l, int r)
    {
        return query(l, r, 1, n, 1);
    }
};

int N, Q;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    LazySegTree seg(N);
    for(int i = 1; i <= N; i++) {
        char p; cin >> p;
        if(p == '(') seg.update_point(i, 1);
        else seg.update_point(i, -1);
    }
    cin >> Q;
    while(Q--) {
        int t, a, b;
        cin >> t >> a >> b;
        if(t == 1) {
            seg.update(a, b);
        } else {
            auto t = seg.query(a, b);
            int ans = -t.lmn + t.rmx + b - a + 1;
            cout << ans << "\n";
        }
    }
}