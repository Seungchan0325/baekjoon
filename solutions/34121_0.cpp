#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;

int lazy[8*MAXN], tree[8*MAXN];

void push(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] += lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int v, int s, int e, int idx)
{
    push(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        lazy[idx] += v;
        push(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = min(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, int s, int e, int idx)
{
    push(s, e, idx);
    if(e < l || r < s) return 1e9;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return min(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int N, Q, sparse[20][MAXN], dep[MAXN];
ll D[MAXN], A[MAXN], B[MAXN], S[MAXN], E[MAXN];
vector<pair<int, ll>> g[MAXN];

void dfs(int u, int p)
{
    for(int i = 1; i < 20; i++) {
        sparse[i][u] = sparse[i-1][sparse[i-1][u]];
    }
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        sparse[0][v] = u;
        dep[v] = dep[u] + 1;
        D[v] = D[u] + w;
        dfs(v, u);
    }
}

int lca(int u, int v)
{
    if(dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for(int i = 0; i < 20; i++) {
        if(diff&(1<<i)) {
            u = sparse[i][u];
        }
    }
    if(u == v) return u;

    for(int i = 19; i >= 0; i--) {
        if(sparse[i][u] != sparse[i][v]) {
            u = sparse[i][u];
            v = sparse[i][v];
        }
    }
    return sparse[0][u];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> Q;
    for(int i = 1; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    dfs(1, -1);

    for(int q = 1; q <= Q; q++) {
        int op; cin >> op;
        if(op == 1) {
            cin >> A[q] >> B[q];
        } else {
            cin >> A[q];
        }
    }

    vector<ll> v = {0, D[N]};
    for(int q = 1; q <= Q; q++) {
        if(B[q] > 0) {
            int r = lca(A[q], N);
            ll d = D[A[q]] - D[r];
            S[q] = -1e18;
            if(d >= B[q]) continue;
            S[q] = D[A[q]]-B[q];
            E[q] = 2*D[r]+B[q]-D[A[q]];
            v.emplace_back(S[q]);
            v.emplace_back(E[q]);
        }
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for(int q = 1; q <= Q; q++) {
        if(B[q] > 0) {
            if(S[q] > -1e18) {
                int s = lower_bound(v.begin(), v.end(), S[q]) - v.begin();
                int e = lower_bound(v.begin(), v.end(), E[q]) - v.begin();
                update(s, e-1, 1, 0, 2*MAXN, 1);
            }
        } else {
            if(S[A[q]] > -1e18) {
                int s = lower_bound(v.begin(), v.end(), S[A[q]]) - v.begin();
                int e = lower_bound(v.begin(), v.end(), E[A[q]]) - v.begin();
                update(s, e-1, -1, 0, 2*MAXN, 1);
            }
        }

        int s = lower_bound(v.begin(), v.end(), 0) - v.begin();
        int e = lower_bound(v.begin(), v.end(), D[N]) - v.begin();
        if(query(s, e-1, 0, 2*MAXN, 1) > 0) cout << "YES\n";
        else cout << "NO\n";
    }
}