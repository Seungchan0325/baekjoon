#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int N, M, L[MAXN], F[MAXN], P[MAXN], num, indeg[MAXN], outdeg[MAXN], cnt[MAXN];
vector<int> g[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
        outdeg[u]++;
    }
    queue<int> q;
    for(int i = 1; i <= N; i++) {
        if(indeg[i] == 0)
            q.push(i);
    }
    while(q.size()) {
        int u = q.front(); q.pop();
        P[num++] = u;
        for(auto v : g[u]) {
            if(--indeg[v] == 0) {
                q.push(v);
            }
        }
    }
    vector<pair<int, int>> vs;
    for(int i = 0; i < N; i++) {
        int u = P[i];
        L[u]++;
        vs.push_back({L[u], u});
        cnt[L[u]]++;
        for(auto v : g[u]) {
            L[v] = max(L[v], L[u]);
        }
    }
    for(int i = N-1; i >= 0; i--) {
        int u = P[i];
        F[u] = 1e9;
        for(auto v : g[u]) {
            F[u] = min(F[u], L[v]);
        }
    }

    sort(vs.begin(), vs.end());
    int mx = 0;
    vector<int> ans;
    for(auto [_, u] : vs) {
        if(cnt[L[u]] == 1 && mx <= L[u]) ans.push_back(u);
        mx = max(mx, F[u]);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(auto i : ans) cout << i << " ";
}
