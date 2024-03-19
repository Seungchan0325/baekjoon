#include <bits/stdc++.h>

using namespace std;

using llint = long long int;

const int MAXN = 100005;
const int LOGN = 17;

llint N, M, sparse[MAXN][LOGN+1][2], depth[MAXN];
vector<pair<int, int>> graph[MAXN];

void dfs(int u, int p)
{
    for(int i = 1; i <= LOGN; i++) {
        sparse[u][i][0] = sparse[sparse[u][i-1][0]][i-1][0];
        sparse[u][i][1] = sparse[sparse[u][i-1][0]][i-1][1] + sparse[u][i-1][1];
    }
    for(auto [v, w] : graph[u]) {
        if(v == p) continue;
        sparse[v][0][0] = u;
        sparse[v][0][1] = w;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

llint lca1(int u, int v)
{
    llint ret = 0;
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for(int i = 0; i <= LOGN; i++) {
        if(diff & (1<<i)) {
            ret += sparse[u][i][1];
            u = sparse[u][i][0];
        }
    }

    if(u == v) return ret;

    for(int i = LOGN; i >= 0; i--) {
        if(sparse[u][i][0] != sparse[v][i][0]) {
            ret += sparse[u][i][1];
            ret += sparse[v][i][1];
            u = sparse[u][i][0];
            v = sparse[v][i][0];
        }
    }
    ret += sparse[u][0][1];
    ret += sparse[v][0][1];
    return ret;
}

int lca2(int u, int v, int k)
{
    int su = u, sv = v;
    int upath, vpath;
    upath = vpath = 1;
    if(depth[u] > depth[v]) {
        int diff = depth[u] - depth[v];
        upath += diff;
        for(int i = 0; i <= LOGN; i++) {
            if(diff & (1<<i)) {
                u = sparse[u][i][0];
            }
        }
    }
    if(depth[u] < depth[v]) {
        int diff = depth[v] - depth[u];
        vpath += diff;
        for(int i = 0; i <= LOGN; i++) {
            if(diff & (1<<i)) {
                v = sparse[v][i][0];
            }
        }
    }

    if(u != v) {
        for(int i = LOGN; i >= 0; i--) {
            if(sparse[u][i][0] != sparse[v][i][0]) {
                u = sparse[u][i][0];
                v = sparse[v][i][0];
                upath += 1<<i;
                vpath += 1<<i;
            }
        }
        upath++; vpath++;
        u = v = sparse[u][0][0];
    }

    if(k <= upath) {
        k--;
        for(int i = 0; i <= LOGN; i++) {
            if(k & (1<<i)) {
                su = sparse[su][i][0];
            }
        }
        return su;
    } else {
        k = vpath + upath - 1 - k;
        for(int i = 0; i <= LOGN; i++) {
            if(k & (1<<i)) {
                sv = sparse[sv][i][0];
            }
        }
        return sv;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    dfs(1, -1);

    cin >> M;
    while(M--) {
        int t;
        cin >> t;
        if(t == 1) {
            int u, v;
            cin >> u >> v;
            llint result = lca1(u, v);
            cout << result << "\n";
        } else {
            int u, v, k;
            cin >> u >> v >> k;
            int result = lca2(u, v, k);
            cout << result << "\n";
        }
    }
}