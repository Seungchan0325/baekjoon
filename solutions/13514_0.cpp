#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;
const int LOGN = 17;

struct EPQ {
    priority_queue<int, vector<int>, greater<int>> pq, erased;
    void push(int v)
    {
        pq.push(v);
    }

    void erase(int v)
    {
        erased.push(v);
    }

    int top()
    {
        while(pq.size() && erased.size() && pq.top() == erased.top()) pq.pop(), erased.pop();
        return pq.top();
    }
    
    bool is_empty()
    {
        while(pq.size() && erased.size() && pq.top() == erased.top()) pq.pop(), erased.pop();
        return pq.empty();
    }
};

bool erased[MAXN], color[MAXN];
int N, M, sz[MAXN], par[MAXN], sparse[MAXN][LOGN+1], depth[MAXN];
vector<int> g[MAXN], cg[MAXN];
EPQ pq[MAXN];

void build(int u, int p)
{
    for(int i = 1; i <= LOGN; i++)
        sparse[u][i] = sparse[sparse[u][i-1]][i-1];
    for(auto v : g[u]) {
        if(v == p) continue;
        sparse[v][0] = u;
        depth[v] = depth[u] + 1;
        build(v, u);
    }
}

int lca(int u, int v)
{
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for(int i = 0; i <= LOGN; i++)
        if(diff & (1<<i))
            u = sparse[u][i];
    
    if(u == v) return u;
    
    for(int i = LOGN; i >= 0; i--)
        if(sparse[u][i] != sparse[v][i]) {
            u = sparse[u][i];
            v = sparse[v][i];
        }
    return sparse[u][0];
}

void dfs(int u, int p)
{
    sz[u] = 1;
    for(auto v : g[u]) {
        if(v == p || erased[v]) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int n, int u, int p)
{
    for(auto v : g[u]) {
        if(v == p || erased[v]) continue;
        if(sz[v] > n/2) return get_cent(n, v, u);
    }
    return u;
}

void DnC(int u, int p)
{
    dfs(u, -1);
    int cent = get_cent(sz[u], u, -1);
    erased[cent] = true;
    par[cent] = p;
    for(auto v : g[cent]) {
        if(erased[v]) continue;
        DnC(v, cent);
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
    build(1, -1);
    DnC(1, -1);

    cin >> M;
    while(M--) {
        int op;
        cin >> op;
        if(op == 1) {
            int i;
            cin >> i;
            if(color[i]) {
                int u = i;
                while(u != -1) {
                    int len = depth[u] + depth[i] - 2 * depth[lca(u, i)];
                    pq[u].erase(len);
                    u = par[u];
                }
                color[i] = 1 - color[i];
            } else {
                int u = i;
                while(u != -1) {
                    int len = depth[u] + depth[i] - 2 * depth[lca(u, i)];
                    pq[u].push(len);
                    u = par[u];
                }
                color[i] = 1 - color[i];
            }
        } else {
            int v;
            cin >> v;

            int ans = 1e9;
            int u = v;
            while(u != -1) {
                int len = depth[u] + depth[v] - 2 * depth[lca(u, v)];
                if(!pq[u].is_empty())
                    ans = min(ans, pq[u].top() + len);
                u = par[u];
            }

            if(ans >= 1e9) cout << "-1\n";
            else cout << ans << "\n";
        }
    }
}