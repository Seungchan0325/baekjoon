#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 30303;

int n, m;
vector<pair<int, ll>> g[MAXN];

pair<ll, int> dfs(int u, int p, ll k)
{
    int ans = 0;
    priority_queue<ll, vector<ll>, greater<>> pq;
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        auto [a, b] = dfs(v, u, k);
        pq.push(a + w);
        ans += b;
    }
    ll mx = 0;
    while(!pq.empty()) {
        if(mx + pq.top() > k) {
            pq.pop();
            ans++;
        } else {
            mx = pq.top();
            pq.pop();
        }
    }
    return pair(mx, ans);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m;
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    ll lo = -1;
    ll hi = 1e12;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(dfs(1, -1, mid).second + 1 > m) lo = mid;
        else hi = mid;
    }
    cout << hi << "\n";
}