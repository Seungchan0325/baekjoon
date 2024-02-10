#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
const int MAXM = 1005;

bool visited[MAXM];
int N, M, owner[MAXM];
vector<int> g[MAXN];

bool match(int u)
{
    for(auto v : g[u]) {
        if(visited[v]) continue;
        visited[v] = true;
        if(owner[v] == -1 || match(owner[v])) {
            owner[v] = u;
            return true;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        for(int j = 0; j < n; j++) {
            int job;
            cin >> job;
            g[i].push_back(job);
        }
    }

    memset(owner, -1, sizeof(owner));

    int ans = 0;
    for(int i = 1; i <= N; i++) {
        memset(visited, 0, sizeof(visited));
        ans += match(i) ? 1 : 0;
    }
    cout << ans;
}