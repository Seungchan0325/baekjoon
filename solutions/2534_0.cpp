#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 303030;
const int MAXP = 1010101;
const int mod = 1e9 + 7;

int N, k, P, U[MAXP], V[MAXP], deg1[MAXN], deg2[MAXN];
vector<int> g1[MAXN], g2[MAXN];

ll pw(ll x, ll n)
{
    ll res = 1;
    x %= mod;
    while(n) {
        if(n&1) res = res*x%mod;
        x = x*x%mod;
        n>>=1;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> k >> P;
    for(int i = 0; i < P; i++) {
        cin >> U[i] >> V[i];
    }

    for(int i = 0; i < P; i++) {
        g1[V[i]].push_back(U[i]);
        g2[U[i]].push_back(V[i]);
        deg1[U[i]]++;
        deg2[V[i]]++;
    }

    priority_queue<int> pq;
    for(int i = 0; i < k; i++) {
        if(deg1[i] == 0) pq.push(-i);
    }
    int p = N-k;
    ll ans = 0;
    while(!pq.empty()) {
        int now = -pq.top(); pq.pop();
        ans = (ans + p * pw(N, now) % mod) % mod;
        p++;
        for(auto nxt : g1[now]) {
            if(--deg1[nxt] == 0) {
                pq.push(-nxt);
            }
        }
    }

    for(int i = 0; i < k; i++) {
        if(deg2[i] == 0) pq.push(-i);
    }
    p = k-1;
    while(!pq.empty()) {
        int now = -pq.top(); pq.pop();
        ans = (ans - p * pw(N, now) % mod + mod) % mod;
        p--;
        for(auto nxt : g2[now]) {
            if(--deg2[nxt] == 0) {
                pq.push(-nxt);
            }
        }
    }
    cout << ans << "\n";
}