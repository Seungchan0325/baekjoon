#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 100005;

int N, Q, P[MAXN], D[MAXN][21], S[MAXN], E[MAXN], pv, tree[4*MAXN], lazy[4*MAXN], subBea[MAXN][21];
vector<int> graph[MAXN];

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] += (e - s + 1) * lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void upd(int l, int r, int v, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        lazy[idx] += v;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) / 2;
    upd(l, r, v, s, m, 2*idx);
    upd(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = tree[2*idx] + tree[2*idx+1];
}

int qry(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return 0;

    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) / 2;
    return qry(l, r, s, m, 2*idx) + qry(l, r, m+1, e, 2*idx+1);
}

void dfs(int u)
{
    S[u] = ++pv;
    D[u][0] = 1;
    for(auto v : graph[u]) {
        dfs(v);
        for(int i = 0; i < 20; i++) {
            D[u][i+1] += D[v][i];
        }
    }
    E[u] = pv;
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(int i = 2; i <= N; i++) cin >> P[i];
    
    for(int i = 2; i <= N; i++) {
        graph[P[i]].push_back(i);
    }

    dfs(1);

    while(Q--) {
        int op;
        cin >> op;

        if(op == 1) {
            int X, Y, K;
            cin >> X >> Y >> K;
            if(K == 1) {
                upd(S[X], E[X], Y);
            } else {
                int s = 0;
                for(int i = 0; i <= 20; i++) {
                    subBea[X][i] += Y;
                    s += D[X][i] * Y;
                    Y /= K;
                }

                upd(S[X], S[X], s);
            }
        } else {
            int X;
            cin >> X;

            int ans = qry(S[X], E[X]);
            for(int d = 1, p = P[X]; p && d <= 20; p = P[p], d++) {
                for(int i = 0; i+d <= 20; i++) {
                    ans += subBea[p][i+d] * D[X][i];
                }
            }

            cout << ans << "\n";
        }
    }
}