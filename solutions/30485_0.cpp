#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

bool erased[MAXN];
int N, sz[MAXN];
pair<int, int> ans[MAXN];
vector<int> g[MAXN];

void get_sz(int u, int p)
{
    sz[u] = 1;
    for(auto v : g[u]) {
        if(v == p || erased[v]) continue;
        get_sz(v, u);
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

void dfs(int u, int p, int d, vector<pair<int, int>>& dists)
{
    dists.emplace_back(d, u);
    for(auto v : g[u]) {
        if(v == p || erased[v]) continue;
        dfs(v, u, d + 1, dists);
    }
}

void DnC(int u)
{
    get_sz(u, -1);
    int c = get_cent(sz[u], u, -1);

    vector<pair<int, int>> dists;
    dfs(c, -1, 0, dists);

    sort(dists.begin(), dists.end(), [](pair<int, int> a, pair<int, int> b) {
        if(a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });

    set<pair<int, int>> s;
    for(auto [dist, idx] : dists) {
        if(s.size()) {
            auto [d, v] = *s.begin();
            if(pair<int, int>{d + dist, v} < ans[idx]) {
                ans[idx] = {d + dist, v};
            }
        }
        s.insert({dist, idx});
    }

    erased[c] = true;
    for(auto v : g[c]) {
        if(erased[v]) continue;
        DnC(v);
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= N; i++) ans[i] = {1e9, i};
    DnC(1);
    for(int i = 1; i <= N; i++) cout << ans[i].second << " ";
}