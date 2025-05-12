#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 101010;

bool vst[MAXN];
ll n, m, c[MAXN], s[MAXN], x[MAXN];
vector<pair<ll, ll>> g[MAXN];
vector<tuple<ll, ll, ll>> edges;

void dfs(ll u)
{
    vst[u] = true;
    for(auto [v, w] : g[u]) {
        if(vst[v]) continue;
        s[v] = -s[u];
        c[v] = w - c[u];
        dfs(v);
    }
}

int main()
{
    cin >> n >> m;
    for(ll i = 1; i <= m; i++) {
        ll a, b, c; cin >> a >> b >> c;
        edges.emplace_back(a, b, c);
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }

    s[1] = 1;
    c[1] = 0;
    dfs(1);

    ll m = 1e9;
    for(auto [u, v, w] : edges) {
        ll s1 = s[u];
        ll s2 = -s[v];
        ll alpba = c[u];
        ll beta = w - c[v];
        if(s1 > s2) swap(s1, s2), swap(alpba, beta);
        if(s1 == s2 && alpba - beta != 0) {
            cout << "No\n";
            return 0;
        }
        if(s1 != s2) {
            if((alpba - beta)&1) {
                cout << "No\n";
                return 0;
            }
            m = (alpba - beta) / 2;
        }
    }

    if(m == 1e9) {
        vector<ll> a;
        for(ll i = 1; i <= n; i++) {
            a.push_back(-s[i] * c[i]);
        }
        sort(a.begin(), a.end());
        m = a[ssize(a)/2];
    }

    for(ll i = 1; i <= n; i++) {
        x[i] = m * s[i] + c[i];
    }

    bool isdone = true;
    for(auto [u, v, w] : edges) {
        if(w != x[u] + x[v]) {
            isdone = false;
            break;
        }
    }
    if(isdone) {
        cout << "Yes\n";
        for(ll i = 1; i <= n; i++) {
            cout << x[i] << " ";
        }
        return 0;
    }

    cout << "No\n";
}