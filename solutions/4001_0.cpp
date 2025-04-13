#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1505;

const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool vst[MAXN][MAXN];
int w, h;
int a[MAXN][MAXN], s[MAXN][MAXN], s1[MAXN][MAXN], s2[MAXN][MAXN];

void bfs(vector<pair<int, int>> s)
{
    memset(vst, 0, sizeof(vst));
    queue<pair<int, int>> q;
    for(auto [x, y] : s) {
        vst[y][x] = true;
        q.emplace(x, y);
    }

    while(!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for(int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 0 || nx > w+1 || ny < 0 || ny > h+2 || a[ny][nx] != 1 || vst[ny][nx]) continue;
            vst[ny][nx] = true;
            q.emplace(nx, ny);
        }
    }
}

int query(int s[MAXN][MAXN], int t, int l, int b, int r)
{
    return s[b][r] - s[t-1][r] - s[b][l-1] + s[t-1][l-1];
}

int main()
{
    cin >> w >> h;
    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            char c;
            cin >> c;
            if(c == '#') a[i][j] = 1;
        }
    }

    
    if(a[1][1] || a[h][w]) {
        int i, j;
        bool found = false;
        for(i = 1; i <= h; i++) {
            for(j = 1; j <= w; j++) {
                if(i == 1 && j == 1) continue;
                if(i == h && j == w) continue;
                if(a[i][j] == 0) {
                    found = true;
                    break;
                }
            }
            if(found) break;
        }
        if(found) cout << "1 " << j << " " << i << "\n";
        else cout << "Impossible\n";
        return 0;
    }

    a[1][1] = 2;
    a[h][w] = 2;
    for(int i = 2; i < w; i++) a[0][i] = a[h+1][i] = 1;
    for(int i = 2; i < h; i++) a[i][0] = a[i][w+1] = 1;

    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];
        }
    }

    bfs({pair{w-1, 0}, pair{w+1, 2}});
    if(vst[h-1][0] || vst[h+2][2]) {
        int i, j;
        bool found = false;
        for(i = 1; i <= h; i++) {
            for(j = 1; j <= w; j++) {
                if(i == 1 && j == 1) continue;
                if(i == h && j == w) continue;
                if(a[i][j] == 0) {
                    found = true;
                    break;
                }
            }
            if(found) break;
        }
        if(found) cout << "1 " << j << " " << i << "\n";
        else cout << "Impossible\n";
        return 0;
    }
    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            for(int k = 0; k < 8; k++) {
                int x = j + dx[k];
                int y = i + dy[k];
                if(vst[y][x]) s1[i][j]++;
            }
            s1[i][j] += s1[i-1][j] + s1[i][j-1] - s1[i-1][j-1];
        }
    }

    bfs({pair{0, h-1}, pair{2, h+1}});
    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            for(int k = 0; k < 8; k++) {
                int x = j + dx[k];
                int y = i + dy[k];
                if(vst[y][x]) s2[i][j]++;
            }
            s2[i][j] += s2[i-1][j] + s2[i][j-1] - s2[i-1][j-1];
        }
    }

    int mx = 1e9;
    int mxx = -1;
    int mxy = -1;
    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            int low1 = -1;
            int low2 = -1;
            {
                int lo = -1;
                int hi = min(w-j, h-i) + 1;
                while(lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    int r = j + mid;
                    int b = i + mid;
                    if(query(s, i, j, b, r)) hi = mid;
                    else lo = mid;
                }
                low1 = lo;
            }
            {
                int lo = -1;
                int hi = min(w-j, h-i) + 1;
                while(lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    int r = j + mid;
                    int b = i + mid;
                    if(query(s1, i, j, b, r) && query(s2, i, j, b, r)) hi = mid;
                    else lo = mid;
                }
                low2 = hi;
            }
            if(low2 <= low1) {
                tie(mx, mxx, mxy) = min(tie(mx, mxx, mxy), tie(low2, j, i));
            }
        }
    }

    if(mx >= 1e9) cout << "Impossible";
    else cout << mx+1 << " " << mxx << " " << mxy;
}