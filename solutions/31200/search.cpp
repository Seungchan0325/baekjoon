#include "stub.h"
#include <bits/stdc++.h>
#include "stub.cpp"

using namespace std;

const int MAXN = 101010;

bool erased[MAXN];
int sz[MAXN], P[MAXN];
vector<int> cond;
vector<int> g[MAXN];

void dfs(int u, int p)
{
    sz[u] = 1;
    for(auto v : g[u]) {
        if(v == p || erased[v]) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int N, int u, int p)
{
    for(auto v : g[u]) {
        if(v == p || erased[v]) continue;
        if(sz[v] > N/2) return get_cent(N, v, u);
    }
    return u;
}

int DnC(int u)
{
    dfs(u, -1);
    int cent = get_cent(sz[u], u, -1);
    erased[cent] = true;
    cond.push_back(cent);
    
    if(ask(cent)) {
        cond.push_back(cent);
        vector<int> c;
        for(auto i : g[cent]) {
            if(erased[i] || i == P[cent]) continue;
            c.push_back(i);
        }
        if(c.size() == 0) return cent;
        if(c.size() == 1) {
            int v = DnC(c[0]);
            if(v == -1) return cent;
            return v;
        }
        if(c.size() == 2) {
            if(!ask(c[0])) swap(c[0], c[1]);
            int v = DnC(c[0]);
            if(v == -1) return cent;
            return v;
        }
    } else {
        if(erased[g[cent][0]]) return -1;
        return DnC(g[cent][0]);
    }
}

int solve(int N, std::vector<int> p){
    for(int i = 0; i < p.size(); i++) {
        g[i+2].push_back(p[i]);
        g[p[i]].push_back(i+2);
        P[i+2] = p[i];
    }
    for(int i = 2; i <= N; i++) {
        for(auto& j : g[i]) {
            if(j == P[i]) swap(j, g[i][0]);
        }
    }
    int ans = DnC(1);
    return ans;
}
