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

const int MAXN = 2020;
const int MAXM = 3030;

bool vst[MAXN];
int N, M, U[MAXM], V[MAXM], W[MAXM], w[MAXN][MAXN], wi[MAXN][MAXN];
vector<int> g[MAXN];

int find(int s, int e)
{
    queue<int> q;
    vector<int> par(N+1);
    q.push(s);
    par[s] = -1;
    while(!q.empty()) {
        auto u = q.front();
        q.pop();
        for(auto v : g[u]) {
            if(par[v]) continue;
            par[v] = u;
            q.push(v);
        }
    }
    assert(par[e] > 0);
    int mx = -1;
    int mxi = -1;
    for(int i = e; par[i] != -1; i = par[i]) {
        if(w[i][par[i]] > mx) {
            mx = w[i][par[i]];
            mxi = wi[i][par[i]];
        }
    }
    assert(mxi > 0);
    w[U[mxi]][V[mxi]] = w[V[mxi]][U[mxi]] = -1;\
    g[U[mxi]].erase(find(g[U[mxi]].begin(), g[U[mxi]].end(), V[mxi]));
    g[V[mxi]].erase(find(g[V[mxi]].begin(), g[V[mxi]].end(), U[mxi]));
    return mxi;
}

int main()
{
    memset(w, -1, sizeof(w));
    cin >> N >> M;
    vector<tuple<int, int, int>> edges;
    for(int i = 1; i <= M; i++) {
        cin >> U[i] >> V[i] >> W[i];
        edges.emplace_back(W[i], i > N-1, i);
        if(i <= N-1) {
            g[U[i]].push_back(V[i]);
            g[V[i]].push_back(U[i]);
        }
    }
    for(int i = 1; i <= N-1; i++) {
        w[U[i]][V[i]] = W[i];
        w[V[i]][U[i]] = W[i];
        wi[U[i]][V[i]] = i;
        wi[V[i]][U[i]] = i;
    }
    sort(edges.begin(), edges.end());
    DSU dsu(N);
    vector<pair<int, int>> ans;
    for(int i = 0; i < M; i++) {
        int j = get<2>(edges[i]);
        if(U[j] == V[j]) continue;
        if(dsu.find(U[j]) != dsu.find(V[j])) {
            dsu.merge(U[j], V[j]);
            if(j > N-1) {
                ans.emplace_back(find(U[j], V[j]), j);
                g[U[j]].push_back(V[j]);
                g[V[j]].push_back(U[j]);
            }
        }
    }
    cout << ans.size() << "\n";
    for(auto [i, j] : ans) cout << i << " " << j << "\n";
}