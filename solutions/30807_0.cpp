#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct DSU {
    vector<int> root;
    DSU(int n) : root(n+1) {
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

struct Edge {
    ll u, v, l, r;
};

ll N, M, K;
vector<Edge> edges;

vector<tuple<ll, int, int>> add(ll k)
{
    vector<tuple<ll, int, int>> e;
    e.reserve(M);
    for(auto [u, v, l, r] : edges) {
        ll d = min(r - l, k);
        k -= d;
        e.emplace_back(l + d, u, v);
    }
    return e;
}

ll mst(vector<tuple<ll, int, int>> e)
{
    sort(e.begin(), e.end());
    ll ans = 0;
    DSU dsu(N);
    for(auto [w, u, v] : e) {
        if(dsu.find(u) != dsu.find(v)) {
            dsu.merge(u, v);
            ans += w;
        }
    }
    return ans;
}

int main()
{
    cin >> N >> M >> K;
    ll diff = 0;
    for(int i = 0; i < M; i++) {
        int u, v, l, r;
        cin >> u >> v >> l >> r;
        Edge e{u, v, l, r};
        edges.push_back(e);
        diff += r - l;
    }
    if(K < mst(add(0)) || mst(add(diff)) < K) {
        cout << "NO\n";
        return 0;
    }

    ll lo = 0;
    ll hi = diff + 1;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(mst(add(mid)) <= K) lo = mid;
        else hi = mid;
    }

    cout << "YES\n";
    for(auto [w, u, v] : add(lo)) {
        cout << w << "\n";
    }
}