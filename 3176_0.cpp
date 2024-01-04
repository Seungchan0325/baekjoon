#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int INF = 987654321;
const int MAXN = 100001;
const int LOG2N = 16;

int n, m, depth[MAXN], parents[MAXN][LOG2N + 1], min_tree[MAXN][LOG2N + 1], max_tree[MAXN][LOG2N + 1];
vector<pii> adjlist[MAXN];

void dfs(int node, int parent, int node_depth) {
    depth[node] = node_depth;
    parents[node][0] = parent;

    for(int i = 1; i <= LOG2N; i++) {
        parents[node][i] = parents[parents[node][i-1]][i-1];
        min_tree[node][i] = min(min_tree[node][i-1], min_tree[parents[node][i-1]][i-1]);
        max_tree[node][i] = max(max_tree[node][i-1], max_tree[parents[node][i-1]][i-1]);
    }
    
    for(auto [next, distance] : adjlist[node]) {
        if(next == parent) continue;
        min_tree[next][0] = distance;
        max_tree[next][0] = distance;
        dfs(next, node, node_depth + 1);
    }
}

//return min, max
pii LCA(int u, int v) {
    int Min = INF;
    int Max = -INF;
    if(depth[u] < depth[v])
        swap(u, v);
    
    int diff = depth[u] - depth[v];
    for(int i = 0; diff != 0; i++) {
        if(diff & 1) {
            Min = min(min_tree[u][i], Min);
            Max = max(max_tree[u][i], Max);
            u = parents[u][i];
        }
        diff /= 2;
    }

    if(u != v) {
        for(int i = LOG2N; i >= 0; i--) {
            if(parents[u][i] != parents[v][i]) {
                Min = min(min_tree[u][i], Min);
                Max = max(max_tree[u][i], Max);
                Min = min(min_tree[v][i], Min);
                Max = max(max_tree[v][i], Max);
                u = parents[u][i];
                v = parents[v][i];
            }
        }
        Min = min(min_tree[u][0], Min);
        Max = max(max_tree[u][0], Max);
        Min = min(min_tree[v][0], Min);
        Max = max(max_tree[v][0], Max);
        u = parents[u][0];
    }

    return {Min, Max};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>n;
    for(int i = 0; i < n - 1; i++) {
        int a, b, c; cin>>a>>b>>c;
        adjlist[a].push_back({b, c});
        adjlist[b].push_back({a, c});
    }
    
    fill(min_tree[0], min_tree[0] + LOG2N + 1, INF);
    fill(max_tree[0], max_tree[0] + LOG2N + 1, -INF);
    fill(min_tree[1], min_tree[1] + LOG2N + 1, INF);
    fill(max_tree[1], max_tree[1] + LOG2N + 1, -INF);
    dfs(1, 0, 1);

    cin>>m;
    for(int i = 0; i < m; i++) {
        int a, b; cin>>a>>b;
        pii result = LCA(a, b);
        cout<<result.first<<" "<<result.second<<"\n";
    }
}