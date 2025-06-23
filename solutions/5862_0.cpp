#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;

int n, p[MAXN], ans[MAXN];
ll L, w[MAXN], offset[MAXN];
priority_queue<ll> pq[MAXN];
vector<int> g[MAXN];

void dfs(int u)
{
    pq[u].push(0);
    for(auto v : g[u]) {
        dfs(v);
        if(pq[v].size() > pq[u].size()) {
            swap(pq[v], pq[u]);
            while(pq[v].size()) {
                pq[u].push(pq[v].top() + offset[u] - offset[v] - w[v]);
                pq[v].pop();
            }
            offset[u] = offset[v] + w[v];
        } else {
            while(pq[v].size()) {
                pq[u].push(pq[v].top() + offset[v] - offset[u] + w[v]);
                pq[v].pop();
            }
        }
    }
    while(pq[u].size() && pq[u].top() + offset[u] > L) pq[u].pop();
    ans[u] = pq[u].size();
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> L;
    for(int i = 2; i <= n; i++) {
        cin >> p[i] >> w[i];
        g[p[i]].push_back(i);
    }
    dfs(1);
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
    }
}