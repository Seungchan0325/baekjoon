#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;

const int dr[] = {0, 0, 1, -1};
const int dc[] = {1, -1, 0, 0};

bool vis[MAXN][MAXN];
int H, W, A[MAXN][MAXN], R[MAXN][MAXN], C[MAXN][MAXN], N[MAXN][MAXN];

void bfs(int sr, int sc)
{
    int cnt = 0;
    queue<pair<int, int>> q;
    q.emplace(sr, sc);
    vis[sr][sc] = true;
    while(!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        R[r][c] = sr;
        C[r][c] = sc;
        cnt++;
        for(int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if(nr < 1 || nr > H || nc < 1 || nc > W || A[r][c] != A[nr][nc] || vis[nr][nc]) continue;
            vis[nr][nc] = true;
            q.emplace(nr, nc);
        }
    }
    N[sr][sc] = cnt;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> H >> W;
    for(int i = 1; i <= H; i++) {
        for(int j = 1; j <= W; j++) {
            cin >> A[i][j];
        }
    }
    for(int i = 1; i <= H; i++) {
        for(int j = 1; j <= W; j++) {
            if(!vis[i][j]) {
                bfs(i, j);
            }
        }
    }
    for(int r = 1; r <= H; r++) {
        for(int c = 1; c <= W; c++) {
            vis[r][c] = false;
        }
    }
    int ans = 0;
    for(int sr = 1; sr <= H; sr++) {
        for(int sc = 1; sc <= W; sc++) {
            if(vis[sr][sc]) continue;
            set<pair<int, int>> chk;
            map<int, int> m;
            queue<pair<int, int>> q;
            q.emplace(sr, sc);
            vis[sr][sc] = true;
            while(!q.empty()) {
                auto [r, c] = q.front(); q.pop();
                R[r][c] = sr;
                C[r][c] = sc;
                for(int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if(nr < 1 || nr > H || nc < 1 || nc > W) continue;
                    if(A[sr][sc] == A[nr][nc]) {
                        if(!vis[nr][nc]) {
                            vis[nr][nc] = true;
                            q.emplace(nr, nc);
                        }
                    } else {
                        if(chk.contains({R[nr][nc], C[nr][nc]})) continue;
                        chk.emplace(R[nr][nc], C[nr][nc]);
                        m[A[R[nr][nc]][C[nr][nc]]] += N[R[nr][nc]][C[nr][nc]];
                    }
                }
            }
            ans = max(ans, N[R[sr][sc]][C[sr][sc]]);
            for(auto [k, i] : m) ans = max(ans, i + N[R[sr][sc]][C[sr][sc]]);
        }
    }
    cout << ans << "\n";
}