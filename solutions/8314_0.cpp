#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, indeg[MAXN];
vector<int> g[MAXN];
vector<pair<int, int>> edges;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(u, v);
        indeg[v]++;
        g[u].push_back(v);
    }

    int cnt = 0;
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(indeg[i] == 0) q.push(i), cnt++;
    }

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(auto v : g[u]) {
            if(--indeg[v] == 0) q.push(v), cnt++;
        }
    }

    if(cnt == n) {
        cout << 1 << "\n";
        cout << edges.size() << " ";
        for(int i = 0; i < edges.size(); i++) cout << i + 1 << " ";
    } else {
        cout << 2 << "\n";
        vector<int> g1, g2;
        for(int i = 0; i < edges.size(); i++) {
            if(edges[i].first < edges[i].second) g1.push_back(i+1);
            else g2.push_back(i+1);
        }
        cout << g1.size() << " ";
        for(auto i : g1) cout << i << " ";
        cout << "\n" << g2.size() << " ";
        for(auto i : g2) cout << i << " ";
    }
}