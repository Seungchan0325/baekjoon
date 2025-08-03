#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 505050;
const int mod = 1e9 + 7;

ll f[MAXN], inv[MAXN];

ll pw(ll x, ll n)
{
    ll ans = 1;
    while(n) {
        if(n&1) ans = ans * x % mod;
        x = x * x % mod;
        n>>=1;
    }
    return ans;
}

void solve()
{
    int N, Q;
    cin >> N >> Q;
    map<int, bool> m;
    vector<int> v = {N+1};
    vector<pair<int, int>> pq; 
    for(int i = 0; i < Q; i++) {
        int p, q; cin >> p >> q;
        pq.emplace_back(p, q);
        m[q+1] = true;
        v.push_back(p); v.push_back(q+1);
    }
    sort(pq.begin(), pq.end());
    int lst = 0;
    for(auto [p, q] : pq) {
        if(p <= lst) {
            cout << "0\n";
            return;
        }
        lst = max(lst, q);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    ll ans = f[v[0]-1];
    // if(m[v[0]]) ans = f[v[0]-1];
    // else ans = f[v[0]];
    for(int i = 1; i < v.size(); i++) {
        int a, b;
        if(m[v[i]]) {
            a = v[i-1]-1;
        } else {
            a = v[i-1];
        }
        b = v[i]-v[i-1]-1;
        ll comb = f[a+b] * (inv[a] * inv[b] % mod) % mod;
        ans = ans * (f[b] * comb % mod) % mod;
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    f[0] = 1;
    for(int i = 1; i < MAXN; i++) f[i] = f[i-1] * i % mod;
    inv[MAXN-1] = pw(f[MAXN-1], mod-2);
    for(int i = MAXN-2; i >= 0; i--) inv[i] = inv[i+1] * (i+1) % mod;

    int t; cin >> t;
    while(t--) solve();
}