#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;
const int INF = 1e9 + 7;

struct Node {
    int mx = -INF;
    int ans = -INF;
    Node() {}
    Node(int v) : mx(v) {}
};

Node merge(Node a, Node b)
{
    Node ret;
    ret.ans = max(a.ans, b.ans);
    ret.mx = max(a.mx, b.mx);
    return ret;
}

struct SegTree {
    int n;
    vector<int> lazy;
    vector<Node> tree;
    void init(int _n)
    {
        n = _n;
        lazy.resize(4*n, INF);
        tree.resize(4*n);
    }
    void push(int s, int e, int idx)
    {
        if(lazy[idx] != INF) {
            tree[idx].ans = max(tree[idx].ans, tree[idx].mx - lazy[idx]);
            if(s != e) {
                lazy[2*idx] = min(lazy[2*idx], lazy[idx]);
                lazy[2*idx+1] = min(lazy[2*idx+1], lazy[idx]);
            }
            lazy[idx] = INF;
        }
    }
    void update(int x, int v, int s, int e, int idx)
    {
        push(s, e, idx);
        if(e < x || x < s) return;
        if(s == e) {
            tree[idx].mx = v;
            return;
        }
        int m = (s + e) / 2;
        update(x, v, s, m, 2*idx);
        update(x, v, m+1, e, 2*idx+1);
        tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
    }
    void update_range(int l, int r, int v, int s, int e, int idx)
    {
        push(s, e, idx);
        if(r < s || e < l) return;
        if(l <= s && e <= r) {
            lazy[idx] = min(lazy[idx], v);
            push(s, e, idx);
            return;
        }
        int m = (s + e) / 2;
        update_range(l, r, v, s, m, 2*idx);
        update_range(l, r, v, m+1, e, 2*idx+1);
        tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
    }
    Node query(int l, int r, int s, int e, int idx)
    {
        push(s, e, idx);
        if(r < s || e < l) return Node();
        if(l <= s && e <= r) return tree[idx];
        int m = (s + e) / 2;
        return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
    }

    void update(int x, int v) { return update(x, v, 1, n, 1); }
    void update_range(int l, int r, int v) { return update_range(l, r, v, 1, n, 1); }
    Node query(int l, int r) { return query(l, r, 1, n, 1); }
};

int N, H[MAXN], A[MAXN], B[MAXN], Q, L[MAXN], R[MAXN], ans[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> H[i] >> A[i] >> B[i];
    cin >> Q;
    for(int i = 1; i <= Q; i++) cin >> L[i] >> R[i];
    
    vector<int> q(Q);
    iota(q.begin(), q.end(), 1);
    sort(q.begin(), q.end(), [](int i, int j){return R[i] < R[j];});
    
    vector<tuple<int, int, int>> add;
    for(int i = 1; i <= N; i++) {
        add.emplace_back(i+A[i], i, 1);
        add.emplace_back(i+B[i]+1, i, 0);
    }
    sort(add.begin(), add.end());

    int j = 0;
    int k = 0;
    SegTree seg1, seg2;
    seg1.init(N);
    seg2.init(N);
    for(int i = 1; i <= N; i++) {
        while(j < add.size() && get<0>(add[j]) <= i) {
            auto [_, idx, op] = add[j++];
            if(op) seg1.update(idx, H[idx]), seg2.update(idx, -H[idx]);
            else seg1.update(idx, -INF), seg2.update(idx, -INF);
        }
        seg1.update_range(i-B[i], i-A[i], H[i]);
        seg2.update_range(i-B[i], i-A[i], -H[i]);
        while(k < q.size() &&  R[q[k]] <= i) {
            int l = L[q[k]];
            int r = R[q[k]];
            ans[q[k]] = max({seg1.query(l, r).ans, seg2.query(l, r).ans, -1});
            k++;
        }
    }
    for(int i = 1; i <= Q; i++) cout << ans[i] << "\n";
}