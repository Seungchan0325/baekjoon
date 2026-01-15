#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;
const ll inf = 1e18;

struct Line {
    ll a, b;
    ll get(ll x) { return a * x + b; }
    Line(ll a = 0, ll b = inf) : a(a), b(b) {}
};

struct Node {
    int l, r;
    Line line;
    Node() : l(-1), r(-1) {}
};

ll N, S[MAXN], V[MAXN], dep[MAXN], dp[MAXN], root[MAXN], pv;
vector<pair<ll, ll>> g[MAXN];
Node tree[35*MAXN];

void update(Line line, ll s, ll e, int idx, int pidx)
{
    if(pidx == -1) {
        tree[idx].line = line;
        return;
    }
    ll m = (s + e) / 2;

    Line low = tree[pidx].line;
    Line high = line;
    if(low.get(s) > high.get(s)) swap(low, high);
    if(low.get(e) <= high.get(e)) {
        tree[idx].line = low;
        tree[idx].l = tree[pidx].l;
        tree[idx].r = tree[pidx].r;
        return;
    }

    if(low.get(m) > high.get(m)) {
        tree[idx].l = pv++;
        tree[idx].r = tree[pidx].r;
        tree[idx].line = high;
        update(low, s, m, tree[idx].l, tree[pidx].l);
    } else {
        tree[idx].l = tree[pidx].l;
        tree[idx].r = pv++;
        tree[idx].line = low;
        update(high, m+1, e, tree[idx].r, tree[pidx].r);
    }
}

ll query(ll x, ll s, ll e, int idx)
{
    if(idx == -1) return inf;
    ll m = (s + e) / 2;
    if(x <= m) return min(tree[idx].line.get(x), query(x, s, m, tree[idx].l));
    else return min(tree[idx].line.get(x), query(x, m+1, e, tree[idx].r));
}

void dfs(int u, int p)
{
    dp[u] = query(V[u], 0, 1e9, root[p]) + V[u] * dep[u] + S[u];
    update(Line(-dep[u], dp[u]), 0, 1e9, root[u] = pv++, root[p]);
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        dep[v] = dep[u] + w;
        dfs(v, u);
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    for(int i = 2; i <= N; i++) cin >> S[i] >> V[i];
    dp[1] = 0;
    update(Line(-dep[1], dp[1]), 0, 1e9, root[1] = pv++, -1);
    for(auto [v, w] : g[1]) {
        dep[v] = w;
        dfs(v, 1);
    }
    for(int i = 2; i <= N; i++) {
        cout << dp[i] << " ";
    }
}