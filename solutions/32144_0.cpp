#include <bits/stdc++.h>

using namespace std;

const int MAXN = 303030;

int n, p[MAXN], dp[MAXN], dp2[MAXN], ans[MAXN];
vector<int> g[MAXN];

struct DataStruct {
    set<pair<int, int>, greater<>> a;
    void insert(int v, int idx) {
        a.emplace(v, idx);
    }
    int query(int n, int ignore) {
        int cnt = 0;
        int ret = 0;
        for(auto [v, idx] : a) {
            if(cnt >= n) break;
            if(idx == ignore) continue;
            ret += v;
            cnt++;
        }
        return ret;
    }
};

void dfs(int u)
{
    DataStruct ds;
    for(auto v : g[u]) {
        dfs(v);
        ds.insert(dp[v] + 1, v);
        dp2[u] = max(dp2[u], dp2[v]);
    }
    dp[u] = ds.query(1, -1);
    dp2[u] = max(dp2[u], ds.query(2, -1));
}

void rdfs(int u, int up, int mx)
{
    vector<pair<int, int>> dpv;
    DataStruct ds1, ds2;
    for(auto v : g[u]) {
        ds1.insert(dp[v] + 1, v);
        ds2.insert(dp2[v], v);
    }
    ds1.insert(up, -1);

    auto qry = [&](int num, int ignore) {
        int cnt = 0;
        int ret = 0;
        for(auto [val, v] : dpv) {
            if(cnt >= num) break;
            if(v == ignore) continue;
            cnt++;
            ret += val;
        }
        return ret;
    };

    ans[u] = max(up + dp2[u], mx);

    for(auto v : g[u]) {
        rdfs(v, ds1.query(1, v) + 1, max({mx, ds1.query(2, v), ds2.query(1, v)}));
        // rdfs(v, qry(1, v)+1, max(mx, qry(2, v)));
    }
}

int main()
{
    cin >> n;
    for(int i = 2; i <= n; i++) {
        cin >> p[i];
        g[p[i]].push_back(i);
    }
    dfs(1);
    rdfs(1, 0, 0);
    for(int i = 2; i <= n; i++) {
        cout << ans[i] << "\n";
    }
}