#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

int N, M, S, P, cash[MAXN], inDeg[MAXN], DP[MAXN];
vector<int> graph[MAXN];
vector<int> target;
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
    cash[x] += cash[y];
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
            merge(u, s.top());
            inStack[s.top()] = false;
            s.pop();
        }

        s.pop();
        inStack[u] = false;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    edges.resize(M);
    for(auto& [u, v] : edges) {
        cin >> u >> v;
        graph[u].push_back(v);
    }
    for(int i = 1; i <= N; i++) cin >> cash[i];
    cin >> S >> P;
    target.resize(P);
    for(auto& i : target) cin >> i;

    iota(root, root + N + 1, 0);
    dfs(S);

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
    q.emplace(find(S));
    DP[find(S)] = cash[find(S)];

    while(!q.empty()) {
        auto u = q.front(); q.pop();
        for(auto v : graph[u]) {
            DP[v] = max(DP[v], cash[v] + DP[u]);
            if(--inDeg[v] == 0) q.push(v);
        }
    }

    int mx = 0;
    for(auto i : target) mx = max(mx, DP[find(i)]);

    cout << mx;
}