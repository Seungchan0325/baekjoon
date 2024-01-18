#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int LG_N = 17;
const int SEG_SZ = 1e7;

int n, m, last, cnt_root, w[MAXN], L[SEG_SZ], R[SEG_SZ], D[SEG_SZ], root[MAXN], tree_to_root[MAXN], dp[MAXN][LG_N+1], depth[MAXN];
vector<int> tree[MAXN];

void build(int node, int start = 0, int end = n-1, int index = 1) {
    if(start == end) {
        D[node] = 0;
        return;
    }

    int mid = (start + end) / 2;
    build(L[node] = last++, start, mid, 2*index);
    build(R[node] = last++, mid+1, end, 2*index+1);
}

void update(int prv, int node, int pos, int delta, int start = 0, int end = n-1, int index = 1) {
    if(start == end) {
        D[node] = D[prv] + delta;
        return;
    }

    int mid = (start + end) / 2;
    if(pos <= mid) {
        L[node] = last++;
        R[node] = R[prv];
        update(L[prv], L[node], pos, delta, start, mid, 2*index);
    } else {
        L[node] = L[prv];
        R[node] = last++;
        update(R[prv], R[node], pos, delta, mid+1, end, 2*index+1);
    }

    D[node] = D[L[node]] + D[R[node]];
}

int query(int node, int left, int right, int start = 0, int end = n-1, int index = 1) {
    if(end < left || right < start) return 0;

    if(left <= start && end <= right) return D[node];

    int mid = (start + end) / 2;
    return query(L[node], left, right, start, mid, 2*index) + query(R[node], left, right, mid+1, end, 2*index+1);
}

void dfs(int node, int parent, int node_depth) {
    tree_to_root[node] = root[cnt_root++] = last++;
    update(tree_to_root[parent], tree_to_root[node], w[node], 1);

    // LCA
    depth[node] = node_depth;
    dp[node][0] = parent;
    for(int i = 1; i <= LG_N; i++)
        dp[node][i] = dp[dp[node][i-1]][i-1];

    for(auto child : tree[node])
        if(child != parent) dfs(child, node, node_depth+1);
}

int lca(int u, int v) {
    if(depth[u] < depth[v]) swap(u, v);

    int diff = depth[u] - depth[v];
    for(int i = 0; diff; i++) {
        if(diff & 1) u = dp[u][i];
        diff >>= 1;
    }

    if(u != v) {
        for(int i = LG_N; i >= 0; i--) {
            if(dp[u][i] != dp[v][i]) {
                u = dp[u][i];
                v = dp[v][i];
            }
        }
        u = dp[u][0];
    }

    return u;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> w[i];
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // coordinate compression
    vector<int> v(w+1, w+n+1);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for(int i = 1; i <= n; i++)
        w[i] = lower_bound(v.begin(), v.end(), w[i]) - v.begin();

    build(tree_to_root[0] = root[cnt_root++] = last++);
    dfs(1, 0, 0);

    while(m--) {
        int x, y, k; cin >> x >> y >> k;

        int p = lca(x, y);
        int pp = dp[p][0];

        int lo = -1, hi = v.size();
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            int cnt = query(tree_to_root[x], 0, mid) + query(tree_to_root[y], 0, mid) - query(tree_to_root[p], 0, mid) - query(tree_to_root[pp], 0, mid);
            if(cnt < k) lo = mid;
            else hi = mid;
        }
        cout << v[hi] << "\n";
    }
}