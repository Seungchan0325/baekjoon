#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 303030;
const int MAXQ = 303030;

bool erased[MAXN], leaf[MAXN], chk[MAXN];
int N, Q, last[MAXN], deg[MAXN], sz[MAXN], U[MAXN], V[MAXN], l[MAXN], r[MAXN];
ll ans[MAXN];
vector<int> t[MAXN], q[MAXN], qs;
vector<pair<int, ll>> g[MAXN];

void dfs(int u, int p)
{
    sz[u] = 1;
    for(auto v : t[u]) {
        if(v == p || erased[v]) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int n, int u, int p)
{
    for(auto v : t[u]) {
        if(v == p || erased[v]) continue;
        if(sz[v] > n/2) return get_cent(n, v, u);
    }
    return u;
}

void get_side(int u, int p)
{
    l[u] = 1e9;
    r[u] = -1e9;
    for(auto v : t[u]) {
        if(v == p || erased[v]) continue;
        get_side(v, u);
        l[u] = min(l[u], l[v]);
        r[u] = max(r[u], r[v]);
    }
    if(leaf[u]) l[u] = r[u] = u;
}

void parse_query(int u, int p)
{
    for(auto i : q[u]) qs.push_back(i);
    for(auto v : t[u]) {
        if(v == p || erased[v]) continue;
        parse_query(v, u);
    }
}

unordered_map<int, ll> dijkstra(int start)
{
    priority_queue<pair<ll, int>> pq;
    unordered_map<int, ll> dist;
    dist[start] = 0;
    pq.emplace(0, start);

    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(d > dist[u]) continue;
        for(auto [v, w] : g[u]) {
            if(!chk[v]) continue;
            ll nd = d + w;
            if(!dist.count(v) || nd < dist[v]) {
                dist[v] = nd;
                pq.emplace(-nd, v);
            }
        }
    }
    return dist;
}

void on(int u, int p)
{
    chk[u] = true;
    for(auto v : t[u]) {
        if(v == p || erased[v]) continue;
        on(v, u);
    }
}

void off(int u, int p)
{
    chk[u] = false;
    for(auto v : t[u]) {
        if(v == p || erased[v]) continue;
        off(v, u);
    }
}

void DnC(int u)
{
    dfs(u, -1);
    int c = get_cent(sz[u], u, -1);

    get_side(c, -1);

    qs.clear();
    parse_query(c, -1);

    on(c, -1);

    auto d = dijkstra(c);
    for(auto i : qs) {
        if(d.count(V[i])) {
            ans[i] = min(ans[i], d[U[i]] + d[V[i]]);
        }
    }

    for(auto v : t[c]) {
        if(erased[v]) continue;
        if(l[v] >= 1e9) continue;
        auto d = dijkstra(l[v]);
        for(auto i : qs) {
            if(d.count(V[i])) {
                ans[i] = min(ans[i], d[U[i]] + d[V[i]]);
            }
        }
    }
    for(auto v : t[c]) {
        if(erased[v]) continue;
        if(r[v] < 0) continue;
        auto d = dijkstra(r[v]);
        for(auto i : qs) {
            if(d.count(V[i])) {
                ans[i] = min(ans[i], d[U[i]] + d[V[i]]);
            }
        }
    }

    off(c, -1);

    erased[c] = true;
    for(auto v : t[c]) {
        if(erased[v]) continue;
        DnC(v);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) last[i] = i;
    
    int n = N;
    for(int i = 2; i <= N; i++) {
        ll p, c;
        cin >> p >> c;
        deg[p]++;
        deg[i]++;

        n++;
        t[n].push_back(last[p]);
        t[last[p]].push_back(n);
        g[n].emplace_back(last[p], 0);
        g[last[p]].emplace_back(n, 0);
        last[p] = n;
        
        t[n].push_back(i);
        t[i].push_back(n);
        g[n].emplace_back(i, c);
        g[i].emplace_back(n, c);
    }

    vector<int> v;
    for(int i = 1; i <= N; i++) {
        if(deg[i] == 1) {
            v.push_back(i);
            leaf[i] = true;
        }
    }

    N = n;

    for(int i = 0; i < v.size(); i++) {
        ll w;
        cin >> w;
        int a = v[i];
        int b = v[(i+1)%v.size()];
        g[a].emplace_back(b, w);
        g[b].emplace_back(a, w);
    }

    cin >> Q;
    for(int i = 1; i <= Q; i++) {
        cin >> U[i] >> V[i];
        q[U[i]].push_back(i);
        ans[i] = 1e18;
    }

    DnC(1);

    for(int i = 1; i <= Q; i++) {
        cout << ans[i] << "\n";
    }
}
