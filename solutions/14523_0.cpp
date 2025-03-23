#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int N;
    vector<int> root;
    DSU(int _N) : N(_N) {
        root.resize(N+1);
        iota(root.begin(), root.end(), 0);
    }

    int find(int x)
    {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }

    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        root[y] = x;
    }
};

struct EPQ {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq, erased;
    void clear()
    {
        while(pq.size() && erased.size() && pq.top() == erased.top()) pq.pop(), erased.pop();
    }
    void push(pair<int, int> x)
    {
        pq.push(x);
    }
    void erase(pair<int, int> x)
    {
        erased.push(x);
    }
    pair<int, int> top()
    {
        clear();
        return pq.top();
    }
    bool empty()
    {
        clear();
        return pq.empty();
    }
};

const int MAXN = 202020;

int N, M, K, Q, A[MAXN], P[MAXN], W[MAXN];
vector<pair<int, int>> g[MAXN];
map<int, EPQ> C[MAXN];
set<pair<int, int>> S[MAXN];
priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
vector<tuple<int, int, int>> edges;

void dfs(int u, int p)
{
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        P[v] = u;
        W[v] = w;
        dfs(v, u);
    }
}

void clear()
{
    while(true) {
        auto [w, u, v] = pq.top();
        if(A[u] == A[v]) {
            pq.pop();
            continue;
        }
        break;
    }
}

void update(int u, int t)
{
    int p = P[u];

    S[p].erase(C[p][A[u]].top());
    C[p][A[u]].erase({W[u], u});
    if(!C[p][A[u]].empty()) S[p].insert(C[p][A[u]].top());
    else C[p].erase(A[u]);

    if(!C[p][t].empty()) S[p].erase(C[p][t].top());
    C[p][t].push({W[u], u});
    S[p].insert(C[p][t].top());
}

void getBest(int u)
{
    for(auto it = S[u].begin(); it != S[u].end(); it++) {
        if(A[it->second] == A[u]) continue;
        pq.emplace(it->first, it->second, u);
        break;
    }
}

void change(int u, int t)
{
    if(P[u] != -1) {
        update(u, t);
        A[u] = t;
        getBest(P[u]);
    }
    A[u] = t;
    getBest(u);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> K >> Q;
    edges.resize(M);
    for(auto& [L, A, B] : edges) cin >> A >> B >> L;
    for(int i = 1; i <= N; i++) cin >> A[i];
    sort(edges.begin(), edges.end());
    DSU dsu(N);
    for(auto [w, u, v] : edges) {
        if(dsu.find(u) != dsu.find(v)) {
            dsu.merge(u, v);
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
            pq.emplace(w, u, v);
        }
    }
    P[1] = -1;
    dfs(1, -1);

    for(int i = 1; i <= N; i++) {
        if(P[i] == -1) continue;
        C[P[i]][A[i]].push({W[i], i});
    }

    for(int i = 1; i <= N; i++) {
        for(auto& item : C[i]) {
            S[i].insert(item.second.top());
        }
    }

    while(Q--) {
        int u, t;
        cin >> u >> t;
        change(u, t);
        clear();
        auto [w, a, b] = pq.top();
        cout << w << "\n";
    }
}