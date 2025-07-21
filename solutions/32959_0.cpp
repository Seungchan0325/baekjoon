#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int N;
    vector<int> root;
    DSU(int _N) : N(_N) {
        root.resize(N);
        iota(root.begin(), root.end(), 0);
    }

    int find(int x)
    {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }

    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        root[y] = x;
    }
};


const int MAXN = 2020;

bool chk[MAXN][MAXN];
int n, m, sx, sy, ex, ey, u[MAXN][MAXN], d[MAXN][MAXN], l[MAXN][MAXN], r[MAXN][MAXN];
char grid[MAXN][MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int t; cin >> t;
    while(t--) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                cin >> grid[i][j];
                if(grid[i][j] == 'S') {
                    sx = i;
                    sy = j;
                } else if(grid[i][j] == 'E') {
                    ex = i;
                    ey = j;
                }
            }
        }

        for(int i = 0; i <= n+1; i++) for(int j = 0; j <= m+1; j++) u[i][j] = d[i][j] = l[i][j] = r[i][j] = chk[i][j] = 0;

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                u[i][j] = grid[i][j] == '#' ? 0 : u[i-1][j] + 1;
                l[i][j] = grid[i][j] == '#' ? 0 : l[i][j-1] + 1;
            }
        }

        for(int i = n; i >= 1; i--) {
            for(int j = m; j >= 1; j--) {
                d[i][j] = grid[i][j] == '#' ? 0 : d[i+1][j] + 1;
                r[i][j] = grid[i][j] == '#' ? 0 : r[i][j+1] + 1;
            }
        }

        vector<DSU> up(m+2, DSU(n+2)), down(m+2, DSU(n+2));
        vector<DSU> left(n+2, DSU(m+2)), right(n+2, DSU(m+2));

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(grid[i][j] == '#') {
                    down[j].merge(i+1, i);
                    up[j].merge(i-1, i);
                    right[i].merge(j+1, j);
                    left[i].merge(j-1, j);
                }
            }
        }

        queue<pair<int, int>> q;
        q.emplace(sx, sy);
        chk[sx][sy] = true;
        while(!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            chk[x][y] = true;
            for(int i = down[y].find(x); i <= x+2*d[x][y]-1 && i <= n; i = down[y].find(i)) {
                q.emplace(i, y);
                down[y].merge(i+1, i);
                up[y].merge(i-1, i);
            }

            for(int i = up[y].find(x); i >= x-2*u[x][y]+1 && i >= 1; i = up[y].find(i)) {
                q.emplace(i, y);
                down[y].merge(i+1, i);
                up[y].merge(i-1, i);
            }

            for(int j = right[x].find(y); j <= y+2*r[x][y]-1 && j <= m; j = right[x].find(j)) {
                q.emplace(x, j);
                right[x].merge(j+1, j);
                left[x].merge(j-1, j);
            }

            for(int j = left[x].find(y); j >= y-2*l[x][y]+1 && j >= 1; j = left[x].find(j)) {
                q.emplace(x, j);
                right[x].merge(j+1, j);
                left[x].merge(j-1, j);
            }
        }

        if(chk[ex][ey]) cout << "YES\n";
        else cout << "NO\n";
    }
}