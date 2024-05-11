#include <bits/stdc++.h>

using namespace std;

const int dl[] = {0, 0, 0, 0, 1, -1}, dr[] = {0, 0, 1, -1, 0, 0}, dc[] = {1, -1, 0, 0, 0, 0};

bool visited[35][35][35];
char building[35][35][35];
tuple<int, int, int> s;

bool inrange(int x, int n)
{
    return 1 <= x && x <= n;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    while(true) {
        int L, R, C;
        cin >> L >> R >> C;
        if(L == 0 && R == 0 && C == 0) break;

        for(int l = 1; l <= L; l++) {
            for(int r = 1; r <= R; r++) {
                for(int c = 1; c <= C; c++) {
                    cin >> building[l][r][c];
                    if(building[l][r][c] == 'S') {
                        s = {l, r, c};
                        visited[l][r][c] = true;
                    }
                }
            }
        }

        memset(visited, 0, sizeof(visited));

        queue<tuple<int, int, int>> q;

        q.push(s);

        int t = 0;
        while(!q.empty()) {
            int sz = q.size();
            for(int i = 0; i < sz; i++) {
                auto [l, r, c] = q.front(); q.pop();
                if(building[l][r][c] == 'E') goto FOUND;
                for(int j = 0; j < 6; j++) {
                    int nl = l + dl[j];
                    int nr = r + dr[j];
                    int nc = c + dc[j];
                    if(!inrange(nl, L) || !inrange(nr, R) || ! inrange(nc, C)) continue;
                    if(building[nl][nr][nc] != '#' && !visited[nl][nr][nc]) {
                        visited[nl][nr][nc] = true;
                        q.emplace(nl, nr, nc);
                    }
                }
            }
            t++;
        }
        cout << "Trapped!\n";
        continue;
FOUND:
        cout << "Escaped in " << t << " minute(s).\n";
    }
}