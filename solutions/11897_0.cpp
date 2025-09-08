#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int N;
    vector<int> root;
    DSU(int _N) : N(_N) {
        root.resize(N);
        iota(root.begin(), root.end(), 0);
    }

    int find(int x)
    {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }

    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        root[y] = x;
        return true;
    }
};

struct Persistent_DSU {
    vector<int> sz, par, tm;
    Persistent_DSU(int N) : sz(N, 1), par(N), tm(N, -1) {
        iota(par.begin(), par.end(), 0);
    }

    int find(int x, int t)
    {
        if(tm[x] > t || x == par[x]) return x;
        return find(par[x], t);
    }

    void merge(int x, int y, int t)
    {
        x = find(x, 1e9);
        y = find(y, 1e9);
        if(x == y) return;
        if(sz[x] < sz[y]) swap(x, y);
        sz[x] += sz[y];
        tm[y] = t;
        par[y] = x;
    }
};

const int MAXE = 202020;
const int MAXQ = 50505;

int V, E, Q, u[MAXE], v[MAXE], L[MAXQ], R[MAXQ];

int main()
{
    cin >> V >> E;
    for(int i = 1; i <= E; i++) cin >> u[i] >> v[i];
    cin >> Q;
    for(int i = 1; i <= Q; i++) cin >> L[i] >> R[i];

    Persistent_DSU prefix(V+5), suffix(V+5);
    for(int i = 1; i <= E; i++) {
        prefix.merge(u[i], v[i], i);
    }
    for(int i = E; i >= 1; i--) {
        suffix.merge(u[i], v[i], E-i);
    }

    for(int i = 1; i <= Q; i++) {
        DSU dsu(V+5);
        for(int j = 1; j <= V; j++) {
            dsu.merge(prefix.find(j, L[i]-1), j);
            dsu.merge(suffix.find(j, E-(R[i]+1)), j);
        }
        vector<int> a; a.reserve(V);
        for(int j = 1; j <= V; j++) {
            a.push_back(dsu.find(j));
        }
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        cout << a.size() << "\n";
    }
}