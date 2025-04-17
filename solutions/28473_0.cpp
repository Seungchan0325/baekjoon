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

int N, M;
vector<tuple<int, int, int, int>> edges;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        edges.emplace_back(x, y, u, v);
    }

    string ans1;
    long long ans = 0;

    DSU dsu(N);
    sort(edges.begin(), edges.end());
    for(auto [x,y,u,v] : edges) {
        if(dsu.find(u) != dsu.find(v)) {
            dsu.merge(u, v);
            ans1 += (x + '0');
            ans += y;
        }
    }
    if(ans1.size() != N - 1) cout << "-1";
    else cout << ans1 << " " << ans;
}