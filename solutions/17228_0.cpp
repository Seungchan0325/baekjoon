#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 500005;
const ll LOGN = 20;

const ll M1 = 543;
const ll M2 = 325;
const ll P1 = 999999391;
const ll P2 = 999999223;

ll N, par[MAXN], h1[MAXN], h2[MAXN], sparse[MAXN][LOGN+1], s[MAXN];
vector<pair<ll, char>> graph[MAXN];

ll pw(ll x, ll n, ll mod)
{
    if(n == 0) return 1;
    if(n & 1) return pw(x, n-1, mod)*x % mod;
    ll half = pw(x, n/2, mod);
    return half*half % mod;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(ll i = 1; i < N; i++) {
        ll u, v;
        char c;
        cin >> u >> v >> c;
        s[v] = c;
        graph[u].emplace_back(v, c);
    }

    string P;
    cin >> P;

    ll ph1 = 0, ph2 = 0;
    for(ll i = 0; i < P.size(); i++) {
        ph1 = (1LL*ph1*M1 + P[i]) % P1;
        ph2 = (1LL*ph2*M2 + P[i]) % P2;
    }

    queue<ll> q;
    q.push(1);
    
    ll ans = 0;

    while(!q.empty()) {
        ll u = q.front(); q.pop();
        for(ll i = 1; i <= LOGN; i++) {
            sparse[u][i] = sparse[sparse[u][i-1]][i-1];
        }

        ll c = u;
        for(ll i = LOGN; i >= 0; i--) {
            if(P.size() & (1 << i)) {
                c = sparse[c][i];
            }
        }

        if(c > 1) {
            h1[u] = (h1[par[u]] - s[c]*pw(M1, P.size()-1, P1) % P1 + P1) * M1 % P1;
            h2[u] = (h2[par[u]] - s[c]*pw(M2, P.size()-1, P2) % P2 + P2) * M2 % P2;
        } else {
            h1[u] = h1[par[u]] * M1 % P1;
            h2[u] = h2[par[u]] * M2 % P2;
        }

        if(par[u] != 0) {
            h1[u] = (h1[u] + s[u]) % P1;
            h2[u] = (h2[u] + s[u]) % P2;
        }

        if(h1[u] == ph1 && h2[u] == ph2) {
            ans++;
        }

        for(auto [v, c] : graph[u]) {
            par[v] = u;
            sparse[v][0] = u;
            q.push(v);
        }
    }

    cout << ans;
}