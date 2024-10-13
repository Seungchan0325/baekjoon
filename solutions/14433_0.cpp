#include <bits/stdc++.h>

using namespace std;

const int MAXN = 305;

bool vst[MAXN];
int N, M, K1, K2, owner[MAXN], cnt1, cnt2;
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
    cin >> N >> M >> K1 >> K2;
    for(int i = 1; i <= K1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    memset(owner, -1, sizeof(owner));
    for(int i = 1; i <= N; i++) {
        memset(vst, 0, sizeof(vst));
        cnt1 += dfs(i);
    }
    for(int i = 1; i <= N; i++) graph[i].clear();
    for(int i = 1; i <= K2; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    memset(owner, -1, sizeof(owner));
    for(int i = 1; i <= N; i++) {
        memset(vst, 0, sizeof(vst));
        cnt2 += dfs(i);
    }

    if(cnt1 >= cnt2) cout << "그만 알아보자";
    else cout << "네 다음 힐딱이";
}