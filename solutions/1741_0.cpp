#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int N;
    vector<int> root;
    DSU(int _N) : N(_N) {
        root.resize(N+1);
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

const int MAXN = 101010;

int n, m, cnt[MAXN];
vector<int> g[MAXN];

int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    DSU dsu(n);
    int mn = 1e9;
    int mni = -1;
    for(int i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end());
        g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
        if(g[i].size() < mn) {
            mn = g[i].size();
            mni = i;
        }
    }
    vector<int> A = g[mni];
    for(int i = 1; i <= n; i++) {
        if(!binary_search(A.begin(), A.end(), i)) dsu.merge(mni, i);
    }
    for(int u = 1; u <= n; u++) {
        for(int j = 0; j < A.size(); j++) {
            int v = A[j];
            if(!binary_search(g[u].begin(), g[u].end(), v)) dsu.merge(u, v);
        }
    }
    for(int i = 1; i <= n; i++) {
        cnt[dsu.find(i)]++;
    }
    vector<int> v;
    for(int i = 1; i <= n; i++) {
        if(i == dsu.find(i)) v.push_back(cnt[dsu.find(i)]);
    }
    sort(v.begin(), v.end());
    cout << v.size() << "\n";
    for(auto i : v) cout << i << " ";
}