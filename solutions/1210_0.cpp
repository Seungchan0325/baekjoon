#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct MF {
    ll n;
    vector<vector<ll>> g, c, f;
    void init(ll _n)
    {
        n = _n;
        g.resize(n);
        c.resize(n, vector<ll>(n));
        f.resize(n, vector<ll>(n));
    }

    void add_edge(ll u, ll v, ll cap)
    {
        g[u].push_back(v);
        g[v].push_back(u);
        c[u][v] = cap;
        c[v][u] = 0;
    }

    ll run(ll s, ll t)
    {
        ll ans = 0;
        while(true) {
            vector<ll> par(n, -1);
            queue<ll> q;
            par[s] = s;
            q.push(s);
            while(!q.empty()) {
                ll u = q.front(); q.pop();
                for(auto v : g[u]) {
                    if(f[u][v] < c[u][v] && par[v] == -1) {
                        par[v] = u;
                        q.push(v);
                    }
                }
            }
            if(par[t] == -1) break;

            ll flow = 1e18;
            for(ll i = t; i != s; i = par[i]) {
                flow = min(flow, c[par[i]][i] - f[par[i]][i]);
            }

            for(ll i = t; i != s; i = par[i]) {
                f[par[i]][i] += flow;
                f[i][par[i]] -= flow;
            }

            ans += flow;
        }

        return ans;
    }

    vector<pair<ll, ll>> get_ans(ll s, ll t)
    {
        ll flow = run(s, t);
        vector<ll> par(n, -1);
        queue<ll> q;
        par[s] = s;
        q.push(s);
        while(!q.empty()) {
            ll u = q.front(); q.pop();
            for(auto v : g[u]) {
                if(f[u][v] < c[u][v] && par[v] == -1) {
                    par[v] = u;
                    q.push(v);
                }
            }
        }

        vector<pair<ll, ll>> ans;

        ll acc = 0;
        for(ll u = 0; u < n; u++) {
            for(auto v : g[u]) {
                if(par[u] != -1 && par[v] == -1) {
                    ans.emplace_back(u, v);
                    acc += c[u][v];
                }
            }
        }

        assert(acc == flow);

        return ans;
    }
};

int main()
{
    ll n, m;
    cin >> n >> m;
    ll s, t;
    cin >> s >> t; s--; t--;
    vector<ll> c(n), in(n), out(n);
    MF mf;
    mf.init(2*n);
    for(ll i = 0; i < n; i++) {
        cin >> c[i];
        in[i] = i<<1;
        out[i] = i<<1|1;
        mf.add_edge(in[i], out[i], c[i]);
    }
    for(ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v; u--; v--;
        mf.add_edge(out[u], in[v], 1e18);
        mf.add_edge(out[v], in[u], 1e18);
    }
    for(auto [u, v] : mf.get_ans(in[s], out[t])) {
        if(u%2==0 && u+1 == v) {
            cout << u/2+1 << " ";
        }
    }
}