#include <bits/stdc++.h>

using namespace std;

const int MAXN = 111;
const int SZ = 10101;

bool vst[SZ];
int n, m, chk[MAXN][MAXN], match[SZ], xx[MAXN][MAXN], yy[MAXN][MAXN];
vector<int> g[SZ];

bool dfs(int u)
{
    vst[u] = true;
    for(auto v : g[u]) {
        if(vst[match[v]]) continue;
        if(match[v] == -1 || dfs(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int main()
{
    cin >> n;
    cin >> m;
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y; x--; y--;
        chk[x][y] = 1;
    }

    int p = 0;
    for(int i = 0; i < n; i++) xx[0][i] = p++;
    for(int i = 1; i < n; i++) xx[i][n-1] = p++;
    for(int i = 1; i < n; i++) {
        for(int j = n-2; j >= 0; j--) {
            if(chk[i][j]) xx[i][j] = p++;
            else xx[i][j] = xx[i-1][j+1];
        }
    }
    int half = p;
    for(int i = n-1; i >= 0; i--) yy[i][0] = p++;
    for(int i = 1; i < n; i++) yy[0][i] = p++;
    for(int i = 1; i < n; i++) {
        for(int j = 1; j < n; j++) {
            if(chk[i][j]) yy[i][j] = p++;
            else yy[i][j] = yy[i-1][j-1];
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(chk[i][j]) continue;
            g[xx[i][j]].push_back(yy[i][j]);
            g[yy[i][j]].push_back(xx[i][j]);
        }
    }

    int ans = 0;
    memset(match, -1, sizeof(match));
    for(int i = 0; i < half; i++) {
        memset(vst, 0, sizeof(vst));
        if(dfs(i)) ans++;
    }
    cout << ans;
}