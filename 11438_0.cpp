#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;
const int LOG2N = 16;

int n, m, depth[MAXN], parents[MAXN][LOG2N + 1];
vector<int> adjlist[MAXN];

void dfs(int node, int parent, int node_depth) {
    depth[node] = node_depth;
    parents[node][0] = parent;

    for(int i = 1; i <= LOG2N; i++)
        parents[node][i] = parents[parents[node][i-1]][i-1];
    
    for(int next : adjlist[node]) {
        if(next == parent) continue;
        dfs(next, node, node_depth + 1);
    }
}

int LCA(int u, int v) {
    if(depth[u] < depth[v])
        swap(u, v);
    
    int diff = depth[u] - depth[v];
    for(int i = 0; diff != 0; i++) {
        if(diff & 1)
            u = parents[u][i];
        diff /= 2;
    }

    if(u != v) {
        for(int i = LOG2N; i >= 0; i--) {
            if(parents[u][i] != parents[v][i]) {
                u = parents[u][i];
                v = parents[v][i];
            }
        }
        u = parents[u][0];
    }

    return u;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>n;
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin>>a>>b;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }

    dfs(1, 0, 1);

    cin>>m;
    for(int i = 0; i < m; i++) {
        int a, b; cin>>a>>b;
        int result = LCA(a, b);
        cout<<result<<"\n";
    }
}