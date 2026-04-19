#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 303030;

struct Node {
    ll a, b, i;
    bool operator < (const Node& t) const {
        return (__int128)a * t.b > (__int128)t.a * b;
    }
    bool operator == (const Node& t) const = default;
};

int N, R, par[MAXN], uf[MAXN];
Node nz[MAXN];
vector<int> g[MAXN];

int find(int x)
{
    if(uf[x] == x) return x;
    return uf[x] = find(uf[x]);
}

void mrg(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    uf[y] = x;
    nz[x].a += nz[y].a;
    nz[x].b += nz[y].b;
}

void dfs(int u, int p)
{
    for(auto v : g[u]) {
        if(v == p) continue;
        par[v] = u;
        dfs(v, u);
    }
}

int main()
{
    cin >> N >> R;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(R, -1);
    ll ans = 0;
    priority_queue<Node> pq;
    for(int i = 1; i <= N; i++) {
        uf[i] = i;
        ans += i;
        nz[i] = {i, 1, i};
        if(i != R) pq.push(nz[i]);
    }
    while(!pq.empty()) {
        auto now = pq.top(); pq.pop();
        if(find(now.i) != now.i || now != nz[now.i]) continue;
        int p = find(par[now.i]);
        ans += nz[p].b * now.a;
        mrg(p, now.i);
        if(p != R) pq.push(nz[p]);
    }
    cout << ans << "\n";
}
