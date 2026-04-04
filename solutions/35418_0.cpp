#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int N, deg[MAXN], num[MAXN], pv;
vector<int> g[MAXN], G[MAXN];

void dfs(int u, int p)
{
    num[u] = ++pv;
    for(auto v : G[u]) {
        if(v == p) continue;
        dfs(v, u);
        cout << num[u] << " " << num[v] << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v; cin >> u >> v;
        deg[u]++; deg[v]++;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    queue<int> q;
    for(int i = 1; i <= N; i++) {
        if(deg[i] == 1) q.push(i);
    }

    int cnt = 0;
    while(!q.empty()) {
        if(q.size() == 2 && ((N-cnt)%2 == 1 || N-cnt == 2)) break;
        int sz = q.size();
        while(sz--) {
            int u = q.front(); q.pop();
            cnt++;
            for(auto v : g[u]) {
                if(--deg[v] == 1) {
                    q.push(v);
                }

                G[v].push_back(u);
            }
        }
    }

    int B = N - cnt;
    cout << B << "\n";
    cout << N / B << "\n";

    dfs(q.front(), -1);
}
