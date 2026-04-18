
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

using ll = long long;

const int MAXN = 202020;

struct AB {
    ll a, b, i;
    bool operator < (const AB& t) const {
        if((b-a>=0)^(t.b-t.a>=0)) return b-a<0;
        if(b-a>=0) return a > t.a;
        else return b < t.b;
    }
};

ll T, n, t, a[MAXN], b[MAXN], par[MAXN], uf[MAXN];
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
    a[x] = -min(-a[x], -a[x]+b[x]-a[y]);
    b[x] = max(b[y], b[x]-a[y]+b[y]);
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
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> T;
    while(T--) {
        cin >> n >> t;
        for(int i = 0; i <= n+1; i++) {
            uf[i] = i;
            g[i].clear();
            a[i] = b[i] = par[i] = 0;
        }
        for(int i = 1; i <= n; i++) {
            int x; cin >> x;
            if(x < 0) a[i] = -x;
            else b[i] = x;
        }
        for(int i = 1; i < n; i++) {
            int u, v; cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        g[t].push_back(n+1);
        g[n+1].push_back(t);
        b[n+1] = 1e14;

        dfs(1, -1);

        priority_queue<AB> pq;
        for(int i = 2; i <= n+1; i++) {
            pq.push({a[i], b[i], i});
        }
        while(pq.size()) {
            auto ab = pq.top(); pq.pop();
            if(ab.a != a[ab.i] || ab.b != b[ab.i]) continue;
            mrg(par[ab.i], ab.i);
            int p = find(ab.i);
            if(p > 1) pq.push({a[p], b[p], p});
        }

        if(a[1] <= 0) cout << "escaped\n";
        else cout << "trapped\n";
    }
}
