#include "evolution.h"

#ifdef LSC_ENV
#include "grader.cpp"
#endif

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505050;

struct DataStruct {
    vector<pair<int, int>> s;
    void insert(int key, int x)
    {
        bool flag = true;
        for(auto& [i, k] : s) {
            if(k == key) {
                i = x;
                flag = false;
            }
        }
        if(flag)
            s.emplace_back(x, key);
        sort(s.begin(), s.end(), greater<>());
        while(s.size() > 3) s.pop_back();
    }
    int get()
    {
        int ans = -1e9;
        if(s.size() >= 1) ans = max(ans, s[0].first);
        if(s.size() >= 2) ans = max(ans, s[1].first + 1);
        return ans;
    }
    int path()
    {
        int ans = 0;
        if(s.size() >= 1) ans = max(ans, s[0].first);
        if(s.size() >= 2) ans = max(ans, s[0].first + s[1].first + 1);
        if(s.size() >= 3) ans = max(ans, s[1].first + s[2].first + 2);
        return ans;
    }
};

int N, par[MAXN], dp[MAXN], sub[MAXN];
DataStruct ds[MAXN];

void init() {
    N = 1;
}

void observation(int P) {
    int u = ++N;
    par[u] = P;

    dp[u] = sub[u] = 0;
    ds[par[u]].insert(u, 0);
    u = par[u];
    int newsub = 0;
    while(dp[u] < ds[u].get() || sub[u] < ds[u].path() || sub[u] < newsub) {
        dp[u] = ds[u].get();
        sub[u] = max(sub[u], ds[u].path());
        sub[u] = max(sub[u], newsub);

        if(u == 1) break;

        newsub = max(newsub, sub[u]);
        ds[par[u]].insert(u, dp[u]);
        u = par[u];
    }
}

int analyze(int R) {
    return sub[R];
}
