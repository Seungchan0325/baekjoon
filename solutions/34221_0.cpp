#include <bits/stdc++.h>

using namespace std;

const int MAXW = 101010;

struct DSU {
    vector<int> uf;
    void init(int n)
    {
        uf.resize(n);
        iota(uf.begin(), uf.end(), 0);
    }
    int find(int x)
    {
        if(x == uf[x]) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        uf[y] = x;
    }
};

struct Node {
    int lazy, cnt;
};

int N, M, W, H, S, E;
DSU dsu;
Node tree[4*MAXW];
set<int> st[MAXW];

void apply(int idx, int v)
{
    if(!tree[idx].cnt) return;
    if(tree[idx].lazy != -1) dsu.merge(tree[idx].lazy, v);
    else tree[idx].lazy = v;
}

void push(int s, int e, int idx)
{
    if(tree[idx].lazy == -1) return;
    if(s != e) {
        apply(2*idx, tree[idx].lazy);
        apply(2*idx+1, tree[idx].lazy);
    } else if(tree[idx].cnt) {
        dsu.merge(*st[s].begin(), tree[idx].lazy);
    }
    tree[idx].lazy = -1;
}

void pull(int s, int e, int idx)
{
    tree[idx].cnt = tree[2*idx].cnt + tree[2*idx+1].cnt;
}

void init(int s = 0, int e = W, int idx = 1)
{
    tree[idx].lazy = -1;
    tree[idx].cnt = 0;
    if(s == e) return;
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
}

void update_range_merge(int l, int r, int v, int s = 0, int e = W, int idx = 1)
{
    push(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        apply(idx, v);
        push(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    update_range_merge(l, r, v, s, m, 2*idx);
    update_range_merge(l, r, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}

void update_inc(int x, int v, int s = 0, int e = W, int idx = 1)
{
    push(s, e, idx);
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx].cnt += v;
        return;
    }
    int m = (s + e) / 2;
    update_inc(x, v, s, m, 2*idx);
    update_inc(x, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}

void force_lazy(int s = 0, int e = W, int idx = 1)
{
    push(s, e, idx);
    if(s != e) {
        int m = (s + e) / 2;
        force_lazy(s, m, 2*idx);
        force_lazy(m+1, e, 2*idx+1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> W >> H;
    cin >> S >> E;
    vector<array<int, 3>> xs, ys; xs.reserve(2*N+4); ys.reserve(M+2);
    ys.push_back({0, H, 0});
    ys.push_back({0, H, W});
    xs.push_back({0, S-1, 0});
    xs.push_back({S+1, W, 0});
    xs.push_back({0, E-1, H});
    xs.push_back({E+1, W, H});
    for(int i = 0; i < N; i++) {
        int x1, x2, y;
        cin >> x1 >> x2 >> y;
        if(y == 0 && x1 <= S && S <= x2) {
            if(x1 <= S-1) xs.push_back({x1, S-1, 0});
            if(S+1 <= x2) xs.push_back({S+1, x2, 0});
        } else if(y == H && x1 <= E && E <= x2) {
            if(x1 <= E-1) xs.push_back({x1, E-1, H});
            if(E+1 <= x2) xs.push_back({E+1, x2, H});
        } else {
            xs.push_back({x1, x2, y});
        }
    }
    for(int i = 0; i < M; i++) {
        int y1, y2, x;
        cin >> y1 >> y2 >> x;
        ys.push_back({y1, y2, x});
    }

    vector<vector<pair<int, int>>> sy(H+1), ey(H+1);
    for(int i = 0; i < ys.size(); i++) {
        sy[ys[i][0]].push_back({ys[i][2], i});
        ey[ys[i][1]].push_back({ys[i][2], i});
    }

    vector<vector<array<int, 3>>> upd(H+1);
    for(int i = 0; i < xs.size(); i++) {
        upd[xs[i][2]].push_back({xs[i][0], xs[i][1], (int)ssize(ys)+i});
    }

    init();
    dsu.init(ys.size()+xs.size());
    for(int i = 0; i <= H; i++) {
        for(auto [x, v] : sy[i]) {
            update_range_merge(x, x, v);
            update_inc(x, 1);
            st[x].insert(v);
        }
        sort(upd[i].begin(), upd[i].end(), [](const auto& a, const auto& b){
            if(a[0] != b[0]) return a[0] < b[0];
            return a[1] > b[1];
        });
        int mx = -1;
        int mxi = -1;
        for(const auto& j : upd[i]) {
            if(mx >= j[0]) {
                dsu.merge(mxi, j[2]);
            }
            if(mx < j[1]) {
                mx = j[1];
                mxi = j[2];
            }
        }
        for(const auto& j : upd[i]) {
            update_range_merge(j[0], j[1], j[2]);
        }
        for(auto [x, v] : ey[i]) {
            update_inc(x, -1);
            st[x].erase(v);
        }
    }
    force_lazy();
    if(dsu.find(0) == dsu.find(1)) cout << "No\n";
    else cout << "Yes\n";
}