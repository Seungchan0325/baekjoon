#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

ll ans = 0;
int n, m, c[MAXN], l[MAXN];
vector<int> g[MAXN];
priority_queue<int> pq[MAXN];

ll dfs(int u)
{
    ll sum = c[u];
    pq[u].push(c[u]);
    for(auto v : g[u]) {
        auto ssum = dfs(v);
        sum += ssum;
        if(pq[u].size() < pq[v].size()) swap(pq[u], pq[v]);
        while(pq[v].size()) {
            pq[u].push(pq[v].top()); pq[v].pop();
        }
    }
    while(pq[u].size()) {
        if(sum > m) {
            sum -= pq[u].top();
            pq[u].pop();
        } else {
            break;
        }
    }
    ans = max<ll>(ans, (ll)l[u] * ssize(pq[u]));
    return sum;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        int p;
        cin >> p >> c[i] >> l[i];
        g[p].push_back(i);
        assert(i != -1 || p == 0);
    }
    dfs(1);
    cout << ans << "\n";
}