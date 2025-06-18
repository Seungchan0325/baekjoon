#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

bool vst[MAXN];
int n, m, num[MAXN], pv;
vector<tuple<int, int, int>> ans;
vector<int> g[MAXN];

bool dfs(int u, int p)
{
    num[u] = ++pv;
    vst[u] = true;
    vector<int> vs;
    for(auto v : g[u]) {
        if(v == p) continue;
        if(!vst[v]) {
            if(!dfs(v, u))
                vs.push_back(v);
        }
        else if(num[v] < num[u])
            vs.push_back(v);
    }
    if(vs.size() % 2) {
        for(int i = 0; i+1 < vs.size(); i+=2)
            ans.emplace_back(vs[i], u, vs[i+1]);
        if(p > 0)
            ans.emplace_back(vs.back(), u, p);
        return true;
    } else {
        for(int i = 0; i+1 < vs.size(); i+=2)
            ans.emplace_back(vs[i], u, vs[i+1]);
        return false;
    }
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= n; i++) {
        if(!vst[i]) {
            dfs(i, -1);
        }
    }
    cout << ans.size() << "\n";
    for(auto [a, b, c] : ans) cout << a << " " << b << " " << c << "\n";
}