#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

struct EPQ {
    priority_queue<int> pq, erased;
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
    
    void pop()
    {
        while(pq.size() && erased.size() && pq.top() == erased.top()) pq.pop(), erased.pop();
        pq.pop();
    }
};

bool erased[MAXN];
int N, M, sz[MAXN], par[MAXN], color[MAXN];
vector<int> t[MAXN];
vector<pair<int, int>> g[MAXN];
EPQ ans;
vector<EPQ> pq[MAXN];
EPQ top[MAXN];
map<int, int> group[MAXN];
map<int, int> dist[MAXN];

void get_sz(int u, int p)
{
    sz[u] = 1;
    for(auto v : t[u]) {
        if(v == p || erased[v]) continue;
        get_sz(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int n, int u, int p)
{
    for(auto v : t[u]) {
        if(v == p || erased[v]) continue;
        if(sz[v] > n/2) return get_cent(n, v, u);
    }
    return u;
}

void dfs(int u, int p, int idx, map<int, int>& group, int d, EPQ& pq, map<int, int>& dist)
{
    group[u] = idx;
    dist[u] = d;
    pq.push(d);
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        dfs(v, u, idx, group, d+w, pq, dist);
    }
}

int sum_top2(EPQ& pq)
{
    if(pq.is_empty()) return -1e9;
    int tmp = pq.top(); pq.pop();
    if(pq.is_empty()) {
        pq.push(tmp);
        return 0;
    }
    int ret = tmp + pq.top();
    pq.push(tmp);
    return ret;
}

void DnC(int u, int p)
{
    get_sz(u, -1);
    int c = get_cent(sz[u], u, -1);
    par[c] = p;

    int m = t[c].size();
    pq[c].resize(m);
    group[c][c] = -1;
    dist[c][c] = 0;
    top[c].push(dist[c][c]);
    for(int i = 0; i < m; i++) {
        auto [v, w] = g[c][i];
        if(erased[v]) continue;
        dfs(v, c, i, group[c], w, pq[c][i], dist[c]);
        top[c].push(pq[c][i].top());
    }

    ans.push(sum_top2(top[c]));

    erased[c] = true;
    for(auto v : t[c]) {
        if(erased[v]) continue;
        DnC(v, c);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        t[u].push_back(v);
        t[v].push_back(u);
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    DnC(1, 0);

    cin >> M;
    for(int i = 1; i <= M; i++) {
        int op;
        cin >> op;
        if(op == 1) {
            int u;
            cin >> u;

            if(!color[u]) {
                color[u] = 1 - color[u];
                int v = u;
                while(v != 0) {
                    ans.erase(sum_top2(top[v]));
                    if(group[v][u] == -1) {
                        top[v].erase(0);
                    } else {
                        if(!pq[v][group[v][u]].is_empty()) top[v].erase(pq[v][group[v][u]].top());
                        pq[v][group[v][u]].erase(dist[v][u]);
                        if(!pq[v][group[v][u]].is_empty()) top[v].push(pq[v][group[v][u]].top());
                    }
                    ans.push(sum_top2(top[v]));
                    v = par[v];
                }
            } else {
                color[u] = 1 - color[u];
                int v = u;
                while(v != 0) {
                    ans.erase(sum_top2(top[v]));
                    if(group[v][u] == -1) {
                        top[v].push(0);
                    } else {
                        if(!pq[v][group[v][u]].is_empty()) top[v].erase(pq[v][group[v][u]].top());
                        pq[v][group[v][u]].push(dist[v][u]);
                        if(!pq[v][group[v][u]].is_empty()) top[v].push(pq[v][group[v][u]].top());
                    }
                    ans.push(sum_top2(top[v]));
                    v = par[v];
                }
            }
        } else {
            int result = ans.top();
            if(result <= -1e9) cout << "-1\n";
            else cout << result << "\n";
        }
    }
}