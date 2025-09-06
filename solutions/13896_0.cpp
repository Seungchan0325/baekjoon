#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int N, Q, R, sz[MAXN], in[MAXN], out[MAXN], pv = 0;
vector<int> g[MAXN], t[MAXN];

void dfs(int u, int p)
{
    in[u] = ++pv;
    sz[u] = 1;
    for(auto v : g[u]) {
        if(v == p) continue;
        t[u].push_back(v);
        dfs(v, u);
        sz[u] += sz[v];
    }
    out[u] = pv;
}

void solve()
{
    cin >> N >> Q >> R;
    for(int i = 1; i < N; i++) {
        int A, B; cin >> A >> B;
        g[A].push_back(B);
        g[B].push_back(A);
    }

    dfs(1, -1);

    while(Q--) {
        int S, U;
        cin >> S >> U;
        if(S == 0) R = U;
        else {
            if(U == R) {
                cout << N << "\n";
            } else if(in[U] <= in[R] && out[R] <= out[U]) {
                int lo = 0;
                int hi = t[U].size();
                while(lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    if(in[t[U][mid]] <= in[R]) lo = mid;
                    else hi = mid;
                }
                cout << N - sz[t[U][lo]] << "\n";
            } else {
                cout << sz[U] << "\n";
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        g[i].clear();
        t[i].clear();
        sz[i] = 0;
        in[i] = 0;
        out[i] = 0;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cout << "Case #" << i << ":\n";
        solve();
    }
}