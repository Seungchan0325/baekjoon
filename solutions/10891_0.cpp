#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

bool iscactus = true;
int n, m, low[MAXN], num[MAXN], dfsn, cycles[MAXN];
vector<int> g[MAXN];
stack<pair<int, int>> s;

void dfs(int u, int p)
{
    num[u] = low[u] = ++dfsn;
    for(auto v : g[u]) {
        if(v == p) continue;
        if(num[v] < num[u]) s.emplace(u, v);
        if(!num[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(num[u] <= low[v]) {
                set<int> vertex;
                int edge = 0;
                while(true) {
                    vertex.insert(s.top().first);
                    vertex.insert(s.top().second);
                    edge++;
                    if(s.top() == pair(u, v)) { s.pop(); break; }
                    s.pop();
                }
                if(vertex.size() >= 3 && edge > vertex.size()) iscactus = false;
                if(vertex.size() >= 3 && edge == vertex.size()) for(auto i : vertex) if(++cycles[i] >= 2) iscactus = false;
            }
        }
        else low[u] = min(low[u], num[v]);
    }
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, -1);
    // for(int i = 1; i <= n; i++) if(!num[i]) dfs(i, -1);
    if(iscactus) cout << "Cactus";
    else cout << "Not cactus";
}