#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

bool vst[MAXN];
int N, M;
vector<int> g[MAXN];
vector<int> p;

void dfs(int u)
{
    vst[u] = true;
    for(auto v : g[u]) {
        if(vst[v]) continue;
        dfs(v);
    }
    p.push_back(u);
}

int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int K = N;
    for(int i = 1; i <= N; i++) {
        if(!vst[i]) {
            dfs(i);
            K--;
            p.pop_back();
        }
    }
    cout << K << "\n";
    for(auto u : p) cout << u << "\n";
}
