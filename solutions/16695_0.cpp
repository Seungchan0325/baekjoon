#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int n;
    vector<int> p, rank;
    stack<tuple<int, int, bool>> st;
    DSU(int n) : n(n), p(n), rank(n, 1)
    {
        iota(p.begin(), p.end(), 0);
    }

    int find(int x)
    {
        if(p[x] == x) return x;
        return find(p[x]);
    }

    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if(x == y) {
            st.emplace(x, y, 0);
            return;
        }
        if(rank[x] < rank[y]) swap(x, y);
        st.emplace(x, y, rank[x] == rank[y]);
        rank[x] += rank[x] == rank[y];
        p[y] = x;
    }

    void rollback(int cnt)
    {
        while(cnt--) {
            auto [x, y, flag] = st.top(); st.pop();
            p[y] = y;
            rank[x] -= flag;
        }
    }
};

struct Query {
    int op, x, y, v;
};

const int MAXN = 100005;

int N, Q, R[MAXN], ans[MAXN];
vector<tuple<int, int, int>> seg[4*MAXN];
vector<DSU> dsu;
Query q[MAXN];

void update(int l, int r, int x, int y, int v, int s, int e, int idx)
{
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        seg[idx].emplace_back(x, y, v);
        return;
    }

    int m = (s + e) / 2;
    update(l, r, x, y, v, s, m, 2*idx);
    update(l, r, x, y, v, m+1, e, 2*idx+1);
}

void DnC(int s, int e, int idx)
{
    for(auto [x, y, v] : seg[idx]) {
        for(int i = v; i <= 9; i++) {
            dsu[i].merge(x, y);
        }
    }

    if(s == e) {
        auto [op, x, y, v] = q[s];

        if(op == 2) {
            ans[s] = -1;
            for(int i = 0; i <= 9; i++) {
                if(dsu[i].find(x) == dsu[i].find(y)) {
                    ans[s] = i;
                    break;
                }
            }
        }
    } else {
        int m = (s + e) / 2;
        DnC(s, m, 2*idx);
        DnC(m+1, e, 2*idx+1);
    }

    for(auto [x, y, v] : seg[idx]) {
        for(int i = v; i <= 9; i++) {
            dsu[i].rollback(1);
        }
    }
}

int main()
{
    cin >> N >> Q;
    map<pair<int, int>, int> L;
    for(int i = 1; i <= Q; i++) {
        auto& [op, x, y, v] = q[i];
        cin >> op;
        if(op == 0) {
            cin >> x >> y >> v;
            if(x > y) swap(x, y);
            L[{x, y}] = i;
            R[i] = Q;
        }
        else if(op == 1) {
            cin >> x >> y;
            if(x > y) swap(x, y);
            R[L[{x, y}]] = i;
        }
        else cin >> x >> y;
    }

    dsu.resize(10, DSU(N));

    for(int i = 1; i <= Q; i++) {
        auto [op, x, y, v] = q[i];
        if(op == 0) {
            update(i, R[i], x, y, v, 1, Q, 1);
        }
    }

    DnC(1, Q, 1);
    for(int i = 1; i <= Q; i++) {
        auto [op, x, y, v] = q[i];
        if(op == 2) {
            cout << ans[i] << "\n";
        }
    }
}