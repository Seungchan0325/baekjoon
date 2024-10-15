#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

bool vst[MAXN];
int N, M, owner[MAXN];
vector<int> graph[MAXN];

bool dfs(int u)
{
    for(auto v : graph[u]) {
        if(vst[v]) continue;
        vst[v] = true;
        if(owner[v] == -1 || dfs(owner[v])) {
            owner[v] = u;
            return true;
        }
    }
    return false;
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    int ans = 0;
    memset(owner, -1, sizeof(owner));
    for(int i = 1; i <= N; i++) {
        memset(vst, 0, sizeof(vst));
        ans += dfs(i);
    }
    cout << ans;
}