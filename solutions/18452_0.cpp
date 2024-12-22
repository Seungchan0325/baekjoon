#include <bits/stdc++.h>

using namespace std;

bool chk[101010];
int n, m;
vector<int> graph[101010];

void dfs(int u)
{
    chk[u] = true;
    for(auto v : graph[u]) {
        if(chk[v]) continue;
        dfs(v);
    }
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    int c = 0;
    for(int i = 1; i <= n; i++) {
        if(!chk[i]) {
            dfs(i);
            c++;
        }
    }
    cout << m - n + c;
}