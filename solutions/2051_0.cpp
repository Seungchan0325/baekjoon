#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

bool visited[MAXN], coverA[MAXN], coverB[MAXN];
int N, M, owner[MAXN], rowner[MAXN];
vector<int> graph[MAXN];

bool dfs(int u)
{
    for(auto v : graph[u]) {
        if(visited[v]) continue;
        visited[v] = true;
        if(owner[v] == -1 || dfs(owner[v])) {
            owner[v] = u;
            rowner[u] = v;
            return true;
        }
    }
    return false;
}

void dfs2(int u)
{
    visited[u] = true;
    for(auto v : graph[u]) {
        coverB[v] = true;
        if(!visited[owner[v]]) dfs2(owner[v]);
    }
}

int main()
{
    cin >> N >> M;
    int n;
    int b;
    for(int i = 1; i <= N; i++) {
        cin >> n;
        for(int j = 0; j < n; j++) {
            cin >> b;
            graph[i].push_back(b);
        }
    }

    int cnt = 0;
    memset(rowner, -1, sizeof(rowner));
    memset(owner, -1, sizeof(owner));
    for(int i = 1; i <= N; i++) {
        memset(visited, 0, sizeof(visited));
        cnt += dfs(i);
    }

    cout << cnt << "\n";

    memset(visited, 0, sizeof(visited));
    for(int i = 1; i <= N; i++) {
        if(rowner[i] == -1) dfs2(i);
    }

    vector<int> A, B;
    for(int i = 1; i <= N; i++) {
        if(rowner[i] != -1 && !visited[i]) A.push_back(i);
    }
    for(int i = 1; i <= M; i++) {
        if(coverB[i]) B.push_back(i);
    }
    cout << A.size() << " ";
    for(auto i : A) cout << i << " ";
    cout << "\n";
    cout << B.size() << " ";
    for(auto i : B) cout << i << " ";
    cout << "\n";
}