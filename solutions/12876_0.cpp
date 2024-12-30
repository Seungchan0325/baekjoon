#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;

struct Line {
    ll a, b;
    ll get(ll x) { return a * x + b; }
};

struct Node {
    int l, r;
    ll s, e;
    Line line;
};

struct LiChao {
    vector<Node> tree;
    void init(ll s, ll e)
    {
        tree.push_back({-1, -1, s, e, {0, -INF}});
    }

    void update(int node, Line v)
    {
        ll s = tree[node].s;
        ll e = tree[node].e;
        ll m = (s + e) / 2;
        Line low = tree[node].line;
        Line high = v;
        if(low.get(s) > high.get(s)) swap(low, high);

        if(low.get(e) <= high.get(e)) {
            tree[node].line = high;
            return;
        }

        if(low.get(m) < high.get(m)) {
            tree[node].line = high;
            if(tree[node].r == -1) {
                tree[node].r = tree.size();
                tree.push_back({-1, -1, m+1, e, {0, -INF}});
            }
            update(tree[node].r, low);
        } else {
            tree[node].line = low;
            if(tree[node].l == -1) {
                tree[node].l = tree.size();
                tree.push_back({-1, -1, s, m, {0, -INF}});
            }
            update(tree[node].l, high);
        }
    }

    ll query(int node, ll x)
    {
        if(node == -1) return -INF;
        ll s = tree[node].s;
        ll e = tree[node].e;
        ll m = (s + e) / 2;
        if(x <= m) return max(tree[node].line.get(x), query(tree[node].l, x));
        else return max(tree[node].line.get(x), query(tree[node].r, x));
    }
};

struct Q {
    int op;
    ll a, b;
    int i;
    ll x;
};

const int MAXN = 300005;

int n, R[MAXN];
ll ans[MAXN];
Q queries[MAXN];
LiChao tree[4*MAXN];

void update(int l, int r, Line v, int s = 1, int e = n, int idx = 1)
{
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        tree[idx].update(0, v);
        return;
    }

    int m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
}

void DnC(int s, int e, int idx)
{
    if(s == e) {
        auto [op, a, b, i, x] = queries[s];
        if(op != 3) return;
        ll res = -INF;
        while(idx > 0) {
            res = max(res, tree[idx].query(0, x));
            idx /= 2;
        }
        ans[s] = res;
        return;
    }
    int m = (s + e) / 2;
    DnC(s, m, 2*idx);
    DnC(m+1, e, 2*idx+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        auto& [op, a, b, j, x] = queries[i];
        cin >> op;
        if(op == 1) {
            cin >> a >> b;
            R[i] = n;
        }
        else if(op == 2) {
            cin >> j;
            R[j] = i;
        }
        else cin >> x;
    }

    for(int i = 0; i < 4*n; i++) tree[i].init(-2e9, 2e9);

    for(int j = 1; j <= n; j++) {
        auto [op, a, b, i, x] = queries[j];
        if(op == 1) {
            update(j, R[j], {a, b});
        }
    }

    DnC(1, n, 1);

    for(int i = 1; i <= n; i++) {
        auto& [op, a, b, j, x] = queries[i];
        if(op == 3) {
            if(ans[i] <= -INF) cout << "EMPTY\n";
            else cout << ans[i] << "\n";
        }
    }
}