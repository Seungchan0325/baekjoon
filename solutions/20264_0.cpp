#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

int n, m, low[MAXN], num[MAXN], dfsn, cut, bridge, bcc, mx_bcc;
vector<int> g[MAXN];
stack<pair<int, int>> s;

void dfs(int u, int p)
{
    int cnt = 0;
    low[u] = num[u] = ++dfsn;
    for(auto v : g[u]) {
        if(v == p) continue;
        if(num[v] < num[u]) s.emplace(u, v);
        if(!num[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(num[u] <= low[v]) {
                cnt++;
                int edge = 0;
                while(true) {
                    edge++;
                    if(s.top() == pair(u, v)) break;
                    s.pop();
                }
                s.pop();
                if(edge == 1) bridge++;
                mx_bcc = max(mx_bcc, edge);
            }
        } else {
            low[u] = min(low[u], num[v]);
        }
    }
    bcc += cnt;
    if(u != 1) cnt++;
    if(cnt >= 2) cut++;
}

int main()
{
    int t; cin >> t;
    while(t--) {
        cin >> n >> m;
        dfsn = cut = bridge = bcc = mx_bcc = 0;
        for(int i = 1; i <= n; i++) {
            low[i] = num[i] = 0;
            g[i].clear();
        }
        for(int i = 1; i <= m; i++) {
            int u, v; cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1, -1);
        int g = gcd(bcc, mx_bcc);
        bcc /= g;
        mx_bcc /= g;
        cout << cut << " " << bridge << " " << bcc << " " << mx_bcc << "\n";
    }    
}