#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;
const int SIZE = MAXN + MAXN;

bool chk[SIZE];
int n, k, owner[SIZE];
vector<int> g[SIZE];

bool dfs(int u)
{
    for(auto v : g[u]) {
        if(chk[v]) continue;
        chk[v] = true;
        if(owner[v] == -1 || dfs(owner[v])) {
            owner[v] = u;
            return true;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> k;
    for(int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;
        c += MAXN;
        g[r].push_back(c);
    }

    int ans = 0;
    memset(owner, -1, sizeof(owner));
    for(int i = 1; i <= n; i++) {
        memset(chk, 0, sizeof(chk));
        if(dfs(i)) ans++;
    }
    cout << ans;
}