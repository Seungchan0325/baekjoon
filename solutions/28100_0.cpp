#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 500005;

bool visited1[MAXN], visited2[MAXN];
int N, M, a, x, y, inDeg[MAXN];
ll b[MAXN], sum[MAXN], DP[MAXN], ans;
vector<int> graph[MAXN], rev_graph[MAXN];
vector<pair<int, int>> edges;

int root[MAXN];

int find(int x)
{
    if(x == root[x]) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;

    root[y] = x;
    sum[x] += sum[y];
}

bool inStack[MAXN];
int pv, num[MAXN], low[MAXN];
stack<int> s;

void dfs(int u)
{
    num[u] = low[u] = ++pv;
    s.push(u);
    inStack[u] = true;

    for(auto v : graph[u]) {
        if(!num[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(inStack[v]) {
            low[u] = min(low[u], low[v]);
        }
    }

    if(num[u] == low[u]) {
        while(s.top() != u) {
            // cout << s.top() << " ";
            merge(u, s.top());
            inStack[s.top()] = false;
            s.pop();
        }
        // cout << u << "\n";

        s.pop();
        inStack[u] = false;
    }
}

void dfs1(int u)
{
    visited1[u] = true;
    for(auto v : graph[u]) {
        if(!visited1[v]) dfs1(v);
    }
}

void dfs2(int u)
{
    visited2[u] = true;
    for(auto v : rev_graph[u]) {
        if(!visited2[v]) dfs2(v);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i <= N; i++) cin >> b[i];
    edges.resize(M);
    for(auto& [u, v] : edges) {
        cin >> u >> v;
    }
    cin >> a >> x >> y;

    // 레버를 당기지 않음
    {
        for(auto [u, v] : edges)
            graph[u].push_back(v);
        iota(root, root + N + 1, 0);
        for(int i = 1; i <= N; i++) sum[i] = b[i];
        dfs(1);

        for(int i = 1; i <= N; i++) {
            graph[i].clear();
        }

        for(auto [u, v] : edges) {
            u = find(u);
            v = find(v);

            if(u == v || !num[v] || !num[u]) continue;
            graph[u].push_back(v);
            inDeg[v]++;
        }

        queue<int> q;
        q.emplace(find(1));
        DP[find(1)] = sum[find(1)];

        while(!q.empty()) {
            auto u = q.front(); q.pop();
            ans = max(ans, DP[u]);
            for(auto v : graph[u]) {
                DP[v] = max(DP[v], sum[v] + DP[u]);
                if(--inDeg[v] == 0) q.push(v);
            }
        }
    }

    // 레버를 당김
    {
        pv = 0;
        iota(root, root + N + 1, 0);
        memset(inStack, 0, sizeof(inStack));
        memset(num, 0, sizeof(num));
        memset(low, 0, sizeof(low));
        memset(sum, 0, sizeof(sum));
        memset(inDeg, 0, sizeof(inDeg));
        memset(DP, 0, sizeof(DP));
        s = stack<int>();
        for(int i = 1; i <= N; i++) graph[i].clear();
        for(int i = 1; i <= N; i++) sum[i] = b[i];

        for(auto [u, v] : edges) {
            graph[u].push_back(v);
            rev_graph[v].push_back(u);
        }

        dfs1(a);
        dfs2(a);

        if(!(visited1[x] || visited1[y]) || !visited2[1]) {
            goto f;
        }

        for(int i = 1; i <= N; i++) graph[i].clear();
        
        edges.emplace_back(x, y);
        edges.emplace_back(y, x);
        for(auto [u, v] : edges) {
            graph[u].push_back(v);
            // rev_graph[v].push_back(u);
        }

        memset(visited1, 0, sizeof(visited1));
        memset(visited2, 0, sizeof(visited2));

        dfs1(a);
        dfs2(a);

        for(int i = 1; i <= N; i++) graph[i].clear();

        for(auto [u, v] : edges) {
            if((visited1[u] || visited2[u]) && (visited1[v] || visited2[v]))
                graph[u].push_back(v);
        }
        dfs(1);

        for(int i = 1; i <= N; i++) graph[i].clear();

        for(auto [u, v] : edges) {
            u = find(u);
            v = find(v);

            if(u == v || !num[v] || !num[u]) continue;
            graph[u].push_back(v);
            inDeg[v]++;
        }

        queue<int> q;
        q.emplace(find(1));
        DP[find(1)] = sum[find(1)];

        while(!q.empty()) {
            auto u = q.front(); q.pop();
            ans = max(ans, DP[u]);
            for(auto v : graph[u]) {
                DP[v] = max(DP[v], sum[v] + DP[u]);
                if(--inDeg[v] == 0) q.push(v);
            }
        }
    }

f:

    cout << ans;
}