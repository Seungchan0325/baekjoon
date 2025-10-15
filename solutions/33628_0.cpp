#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int N, Q, uf[MAXN], sparse[MAXN][20], dep[MAXN];
vector<int> v[MAXN], g[MAXN];

void dfs(int u, int p)
{
    for(int i = 1; i < 20; i++) {
        sparse[u][i] = sparse[sparse[u][i-1]][i-1];
    }
    for(auto v : g[u]) {
        if(v == p) continue;
        dep[v] = dep[u] + 1;
        sparse[v][0] = u;
        dfs(v, u);
    }
}

int find(int x)
{
    if(uf[x] == x) return x;
    return uf[x] = find(uf[x]);
}

void mrg(int x, int y)
{
    int a = find(x);
    int b = find(y);
    if(a == b) return;
    if(a > b) swap(x, y), swap(a, b);
    uf[b] = a;
    if(v[a].size() < v[b].size()) swap(v[a], v[b]), swap(x, y);
    dep[y] = dep[x] + 1;
    sparse[y][0] = x;
    dfs(y, x);
    v[a].insert(v[a].end(), v[b].begin(), v[b].end());
}

int lca(int x, int y)
{
    if(dep[x] < dep[y]) swap(x, y);
    int diff = dep[x]-dep[y];
    for(int i = 0; i < 20; i++) if(diff&(1<<i)) x = sparse[x][i];
    if(x == y) return x;
    for(int i = 19; i >= 0; i--) {
        if(sparse[x][i] != sparse[y][i]) {
            x = sparse[x][i];
            y = sparse[y][i];
        }
    }
    return sparse[x][0];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(int i = 1; i <= N; i++) uf[i] = i, v[i] = {i};
    int last_ans = 0;
    while(Q--) {
        int T, A, B;
        cin >> T >> A >> B; A ^= last_ans; B ^= last_ans;
        if(T == 1) {
            g[A].push_back(B);
            g[B].push_back(A);
            mrg(A, B);
        } else {
            if(find(A) != find(B)) {
                cout << "0\n";
                last_ans = 0;
            } else {
                int C = find(A);
                int ans = lca(A, B) ^ lca(B, C) ^ lca(A, C);
                cout << ans << "\n";
                last_ans = ans;
            }
        }
    }
}