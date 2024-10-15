#include <bits/stdc++.h>

using namespace std;

const int MAXR = 75;
const int MAXK = 505;

const int dr[2][2] = {
    {0, 1},
    {-1, 0},
};

bool isable[MAXR][MAXR], vst[MAXR*MAXR];
int R, C, K, X[MAXK], Y[MAXK], LC[MAXR], RC[MAXR], owner[MAXR*MAXR];
vector<int> graph[MAXR*MAXR];

int IDX(int r, int c) { return r * C + c; }

bool dfs(int u)
{
    for(auto v : graph[u]) {
        if(vst[v]) continue;
        vst[v] = true;
        if(owner[v] == -1 || dfs(owner[v])) {
            owner[u] = v;
            owner[v] = u;
            return true;
        }
    }
    return false;
}

void solve()
{
    cin >> R >> C >> K;
    for(int i = 1; i <= K; i++) cin >> X[i];
    for(int i = 1; i <= K; i++) cin >> Y[i];

    memset(isable, 0, sizeof(isable));
    for(int r = 1; r <= R; r++)
        for(int c = 1; c <= C; c++)
            isable[r][c] = true;

    for(int i = 1; i <= K; i++) {
        isable[X[i]][Y[i]] = false;
    }

    memset(LC, 0, sizeof(LC));
    memset(RC, 0, sizeof(RC));

    for(int r = 1; r <= R; r++)
        for(int c = 1; c <= C; c++)
            graph[IDX(r, c)].clear();

    memset(owner, -1, sizeof(owner));
    int cover = 0;
    for(int c = 1; c <= C; c++) {
        for(int r = 1; r <= R; r++) {
            if(!isable[r][c]) continue;
            for(auto dr : dr[c&1]) {
                int nr = r + dr;
                int nc = c - 1;
                if(isable[r][c] && isable[nr][nc]) {
                    graph[IDX(r, c)].push_back(IDX(nr, nc));
                    graph[IDX(nr, nc)].push_back(IDX(r, c));
                }
            }

            memset(vst, 0, sizeof(vst));
            cover += dfs(IDX(r, c));
        }
        LC[c] = cover;
    }
    
    for(int r = 1; r <= R; r++)
        for(int c = 1; c <= C; c++)
            graph[IDX(r, c)].clear();

    memset(owner, -1, sizeof(owner));
    cover = 0;
    for(int c = C; c >= 1; c--) {
        for(int r = 1; r <= R; r++) {
            if(!isable[r][c]) continue;
            for(auto dr : dr[c&1]) {
                int nr = r + dr;
                int nc = c + 1;
                if(isable[r][c] && isable[nr][nc]) {
                    graph[IDX(r, c)].push_back(IDX(nr, nc));
                    graph[IDX(nr, nc)].push_back(IDX(r, c));
                }
            }

            memset(vst, 0, sizeof(vst));
            cover += dfs(IDX(r, c));
        }
        RC[c] = cover;
    }

    int ans = 0;
    int tot = 0;
    for(int r = 1; r <= R; r++) for(int c = 1; c <= C; c++) if(isable[r][c]) tot++;

    for(int c = 1; c <= C; c++) {
        int cnt = 0;
        for(int r = 1; r <= R; r++) if(isable[r][c]) cnt++;
        if(!cnt) continue;
        ans = max(ans, tot - cnt - LC[c-1] - RC[c+1]);
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int tc;
    cin >> tc;
    while(tc--) solve();
}