#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

bool visited[MAXN], chk[MAXN];
int N, root[MAXN], edge[MAXN], sz[MAXN], inDeg[MAXN], ans[MAXN];
vector<pair<int, int>> graph[MAXN];
vector<tuple<int, int, int>> edges;

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);

    if(x == y) return;

    root[y] = x;
    sz[x] += sz[y];
    edge[x] += edge[y];
}

void dfs(int u)
{
    bool flag = true;
    chk[u] = true;
    for(auto [v, idx] : graph[u]) {
        if(!chk[v] && !visited[v]) {
            ans[idx] = u;
            dfs(v);
            flag = false;
        }
    }

    if(flag) {
        // assert(graph[u].size() == 1);
        for(auto [v, idx] : graph[u]) {
            if(!ans[idx]) {
                ans[idx] = u;
            }
        }
    }
}

int main()
{
    cin >> N;

    vector<int> vs;
    iota(root, root + MAXN, 0);
    fill(sz, sz + MAXN, 1);
    for(int i = 1; i <= N; i++) {
        int u, v;
        cin >> u >> v;
        vs.push_back(u);
        vs.push_back(v);

        edges.emplace_back(u, v, i);
        merge(u, v);
        edge[find(u)]++;

        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
        inDeg[u]++;
        inDeg[v]++;
    }

    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());

    queue<int> q;
    vector<int> arr;

    for(int i : vs) {
        int u = find(i);
        if(sz[u] < edge[u]) {
            cout << "-1";
            return 0;
        }

        if(inDeg[i] == 1) {
            arr.push_back(i);
        }
    }
    
    for(int s : arr) {
        if(visited[s]) continue;

        q.push(s);
        visited[s] = true;
        while(!q.empty()) {
            auto u = q.front(); q.pop();
            for(auto [v, idx] : graph[u]) {
                if(!visited[v]) ans[idx] = u;
                if(--inDeg[v] == 1) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    for(auto i : vs) {
        if(!visited[i]) {
            dfs(i);
        }
    }

    // for(int i = 1; i <= N; i++) {
    //     if(ans[i]) continue;
    //     auto [u, v, idx] = edges[i-1];
    //     if(!chk[u]) {
    //         ans[i] = u;
    //         chk[u] = true;
    //     } else if(!chk[v]) {
    //         ans[i] = v;
    //         chk[v] = true;
    //     }
    // }

    for(int i = 1; i <= N; i++) {
        cout << ans[i] << "\n";
    }
}