#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

ll ans;
int n, m, q, num[MAXN], low[MAXN], dfsn, bcc, vtx[MAXN];
map<pair<int, int>, int> idx, cost;
set<tuple<int, int, int>> used[MAXN], e[MAXN];
vector<int> g[MAXN];
stack<pair<int, int>> s;

void dfs(int u, int p)
{
    num[u] = low[u] = ++dfsn;
    for(auto v : g[u]) {
        if(v == p) continue;
        if(num[v] < num[u]) s.emplace(u, v);
        if(!num[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(num[u] <= low[v]) {
                bcc++;
                set<int> vtxs;
                while(true) {
                    auto [x, y] = s.top();
                    if(x > y) swap(x, y);
                    vtxs.insert(x);
                    vtxs.insert(y);
                    idx[pair(x, y)] = bcc;
                    if(s.top() == pair(u, v)) break;
                    s.pop();
                }
                s.pop();
                vtx[bcc] = vtxs.size();
            }
        } else {
            low[u] = min(low[u], num[v]);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m >> q;
    for(int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        if(u > v) swap(u, v);
        cost[pair(u, v)] = w;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, -1);
    for(auto [k, i] : idx) {
        auto [u, v] = k;
        e[i].emplace(cost[k], u, v);
    }
    for(int i = 1; i <= bcc; i++) {
        int cnt = 0;
        vector<tuple<int, int, int>> erased;
        for(auto [w, u, v] : e[i]) {
            if(w >= 0 && cnt >= vtx[i]-1) break;
            cnt++;
            ans += w;
            erased.emplace_back(w, u, v);
            used[i].emplace(w, u, v);
        }
        for(auto j : erased) e[i].erase(j);
    }
    cout << ans << "\n";
    while(q--) {
        int u, v, w;
        cin >> u >> v >> w;
        if(u > v) swap(u, v);
        int bi = idx[pair(u, v)];
        int oldw = cost[pair(u, v)];
        cost[pair(u, v)] = w;
        if(used[bi].contains(tuple(oldw, u, v))) used[bi].erase(tuple(oldw, u, v)), ans -= oldw;
        else e[bi].erase(tuple(oldw, u, v));
        e[bi].emplace(w, u, v);

        if(used[bi].size()) {
            auto back = *used[bi].rbegin();
            ans -= get<0>(back);
            used[bi].erase(back);
            e[bi].insert(back);
        }

        vector<tuple<int, int, int>> erased;
        for(auto [w, u, v] : e[bi]) {
            if(w >= 0 && used[bi].size() >= vtx[bi]-1) break;
            ans += w;
            erased.emplace_back(w, u, v);
            used[bi].emplace(w, u, v);
        }
        for(auto j : erased) e[bi].erase(j);

        cout << ans << "\n";
    }
}