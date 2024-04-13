#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;

int N, M, K, U, V;
vector<pair<int, int>> edges;
ll root[MAXN], sz[MAXN];

int find(int u)
{
    if(root[u] == u) return u;
    return root[u] = find(root[u]);
}

void Union(int u, int v)
{
    u = find(u);
    v = find(v);

    if(u == v) return;
    root[v] = u;
    sz[u] += sz[v];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K;

    iota(root, root + N + 1, 0);
    fill(sz, sz + N + 1, 1);
    for(int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;
        if(i != K) {
            Union(u, v);
        } else {
            U = u;
            V = v;
        }
    }

    ll ans = 0;
    if(find(U) != find(V)) {
        ans += sz[find(U)] * sz[find(V)];
    }

    cout << ans;
}