#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

int N, sz[MAXN];
vector<int> graph[MAXN], ans;

void dfs(int u, int p)
{
    sz[u]++;
    for(auto v : graph[u]) {
        if(v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

void getCent(int u, int s, int p)
{
    bool flag = false;
    for(auto v : graph[u]) {
        if(v == p) continue;
        if(sz[v] * 2 >= s) {
            getCent(v, s, u);
        }
        if(sz[v] * 2 > s) {
            flag = true;
        }
    }
    if(2*(s - sz[u]) > s) flag = true;
    if(!flag) {
        ans.push_back(u);
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1, -1);
    getCent(1, sz[1], -1);
    sort(ans.begin(), ans.end());
    for(auto i : ans) cout << i << "\n";
}