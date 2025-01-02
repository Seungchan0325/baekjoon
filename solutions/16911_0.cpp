#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, M, A[MAXN], B[MAXN], ans[MAXN];
vector<pair<int, int>> seg[4*MAXN];

struct DSU {
    int n;
    vector<int> parent, rank;
    stack<tuple<int, int, int>> s;
    DSU(int n) : n(n), parent(n + 1), rank(n + 1, 1)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        if(parent[x] == x) return x;
        return find(parent[x]);
    }

    void Union(int x, int y)
    {
        x = find(x);
        y = find(y);
        if(x == y) {
            s.emplace(x, x, 0);
            return;
        }

        if(rank[x] < rank[y]) swap(x, y);

        s.emplace(x, y, rank[x] == rank[y]);
        parent[y] = x;
        rank[x] += rank[x] == rank[y];
    }

    void rollback(int cnt) {
        while(cnt--) {
            auto [x, y, flag] = s.top(); s.pop();
            parent[y] = y;
            rank[x] -= flag;
        }
    }
} dsu(MAXN);

void update(int l, int r, int u, int v, int s = 1, int e = M, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        seg[idx].emplace_back(u, v);
        return;
    }

    int m = (s + e) / 2;
    update(l, r, u, v, s, m, 2*idx);
    update(l, r, u, v, m+1, e, 2*idx+1);
}

void DnC(int l, int r, int idx)
{
    if(l == r) {
        for(auto [u, v] : seg[idx]) dsu.Union(u, v);
        ans[l] = (dsu.find(A[l]) == dsu.find(B[l]));
        dsu.rollback(seg[idx].size());
        return;
    }

    for(auto [u, v] : seg[idx]) {
        dsu.Union(u, v);
    }
    int m = (l + r) / 2;
    DnC(l, m, 2*idx);
    DnC(m+1, r, 2*idx+1);
    dsu.rollback(seg[idx].size());
}

int main()
{
    cin >> N >> M;

    vector<tuple<int, int, int>> upd;
    for(int i = 1; i <= M; i++) {
        int op, a, b;
        cin >> op >> a >> b;
        if(a > b) swap(a, b);
        if(op == 1) {
            upd.emplace_back(a, b, i);
        } else if(op == 2) {
            upd.emplace_back(a, b, i);
        } else {
            A[i] = a;
            B[i] = b;
        }
    }

    sort(upd.begin(), upd.end());

    for(int i = 0; i < upd.size();) {
        auto [u, v, l] = upd[i];
        auto [_u, _v, r] = upd[(i+1)%upd.size()];
        if(_u != u || v != _v || i == (int)upd.size()-1) update(l, M, u, v), i++;
        else update(l, r, u, v), i+=2;
    }

    DnC(1, M, 1);
    for(int i = 1; i <= M; i++) {
        if(A[i]) cout << ans[i] << "\n";
    }
}