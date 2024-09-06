#include <bits/stdc++.h>

using namespace std;

using iii = tuple<int, int, int>;

const int MAXN = 100005;
const int MAXQ = 100005;
const int MAXW = 1000005;

int N, M, Q, L[MAXQ], R[MAXQ], U[MAXQ], V[MAXQ], ans[MAXQ], ans2[MAXQ], root[MAXN], sz[MAXN];
vector<pair<int, int>> edges[MAXW];

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    root[y] = x;
    sz[x] += sz[y];
}

int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[w].emplace_back(u, v);
    }

    cin >> Q;

    for(int i = 0; i < Q; i++) {
        L[i] = -1;
        R[i] = 1000001;
        cin >> U[i] >> V[i];
    }

    while(true) {
        vector<vector<int>> v(MAXW);
        bool is_done = true;
        for(int i = 0; i < Q; i++) {
            if(L[i] + 1 == R[i]) {
                ans[i] = R[i];
                continue;
            }

            is_done = false;
            int m = (L[i] + R[i]) / 2;
            v[m].push_back(i);
        }
        if(is_done) break;

        // fill(sz, sz + N + 1, 1);
        iota(root, root + N + 1, 0);
        for(int i = 0; i < MAXW; i++) {
            for(auto [u, v] : edges[i]) merge(u, v);
            for(auto q : v[i]) {
                if(find(U[q]) == find(V[q])) {
                    R[q] = i;
                } else {
                    L[q] = i;
                }
            }
        }
    }

    vector<vector<int>> v(MAXW);
    for(int i = 0; i < Q; i++) v[ans[i]].push_back(i);

    fill(sz, sz + N + 1, 1);
    iota(root, root + N + 1, 0);
    for(int i = 0; i < MAXW; i++) {
        for(auto [u, v] : edges[i]) merge(u, v);
        for(auto q : v[i]) {
            ans2[q] = sz[find(U[q])];
        }
    }

    for(int i = 0; i < Q; i++) {
        if(ans[i] == 1000001) cout << "-1\n";
        else cout << ans[i] << " " << ans2[i] << "\n";
    }
}