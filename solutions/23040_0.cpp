#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

bool visited[MAXN], isblack[MAXN];
int N, root[MAXN], sz[MAXN];
vector<int> g[MAXN];

int find(int u)
{
    if(root[u] == u) return u;
    return root[u] = find(root[u]);
}

void merge(int u, int v)
{
    u = find(u);
    v = find(v);
    if(u == v) return;
    root[u] = v;
    sz[v] += sz[u];
}

void dfs(int u)
{
    visited[u] = true;
    for(auto v : g[u]) {
        if(visited[v] || isblack[v]) continue;
        merge(u, v);
        dfs(v);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for(int u = 1; u <= N; u++) {
        char c;
        cin >> c;
        if(c == 'B') isblack[u] = true;
    }

    iota(root, root + N + 1, 0);
    fill(sz + 1, sz + N + 1, 1);

    for(int u = 1; u <= N; u++) {
        if(!isblack[u] && !visited[u]) {
            dfs(u);
        }
    }

    long long result = 0;
    for(int u = 1; u <= N; u++) {
        if(isblack[u]) {
            for(auto v : g[u]) {
                if(isblack[v]) continue;
                result += sz[find(v)];
            }
        }
    }

    cout << result;
}