#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;
const int MAXM = 10005;

int n, m, cost[MAXM];
vector<int> graph[MAXN];

using pii = pair<int, int>;

pair<pii, pii> dfs(int u, int p)
{
    int sum = 0;
    vector<int> colors;
    vector<vector<pii>> a(m);
    for(auto v : graph[u]) {
        if(v == p) continue;
        auto [first, alternative] = dfs(v, u);
        if(a[first.second].empty()) colors.push_back(first.second);
        a[first.second].emplace_back(first.first, alternative.first);
        sum += first.first;
    }

    priority_queue<pii, vector<pii>, greater<pii>> q;
    for(int color : colors) {
        for(auto [first, alternative] : a[color]) sum += alternative - first;
        q.emplace(sum + cost[color], color);
        for(auto [first, alternative] : a[color]) sum -= alternative - first;
    }

    int cnt = 0;
    for(int color = 0; color < m && cnt < 2; color++) {
        if(!a[color].empty()) continue;
        q.emplace(sum + cost[color], color);
        cnt++;
    }
    pii first = q.top(); q.pop();
    pii alternative = q.top(); q.pop();
    return {first, alternative};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cin >> m;
    for(int i = 0; i < m; i++) {
        cin >> cost[i];
    }
    sort(cost, cost + m);

    auto [first, alternative] = dfs(1, -1);
    cout << first.first;
}