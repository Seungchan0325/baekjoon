#include <bits/stdc++.h>

using namespace std;

const int dr[] = {0, 1, 0, -1};
const int dc[] = {1, 0, -1, 0};

bool visited[30][30];
char board[30][30];
int traffic_state[10];
int remain_time[10];
tuple<char, int, int> traffic_light[10];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m;
    while(cin >> n >> m) {
        if(n == 0 && m == 0) break;
        int traffic = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cin >> board[i][j];
                if(isdigit(board[i][j])) traffic++;
            }
        }

        for(int i = 0; i < traffic; i++) {
            int j, a, b;
            char c;
            cin >> j >> c >> a >> b;
            traffic_light[j] = make_tuple(c, a, b);
        }

        for(int i = 0; i < traffic; i++) {
            auto [c, a, b] = traffic_light[i];
            traffic_state[i] = c == '-' ? 0 : 1;
            remain_time[i] = c == '-' ? a : b;
        }

        memset(visited, 0, sizeof(visited));
        queue<tuple<int, int, int>> q;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(board[i][j] == 'A') {
                    q.emplace(i, j, 0);
                    visited[i][j] = true;
                    goto EXIT_LOOP;
                }
            }
        }
        EXIT_LOOP:

        while(!q.empty()) {
            int sz = q.size();
            for(int i = 0; i < sz; i++) {
                auto [r, c, t] = q.front(); q.pop();
                if(board[r][c] == 'B') {
                    cout << t << "\n";
                    goto EXIT_LOOP2;
                }
                for(int j = 0; j < 4; j++) {
                    int nr = r + dr[j];
                    int nc = c + dc[j];
                    if(nr < 0 || n <= nr || nc < 0 || m <= nc || visited[nr][nc]) continue;
                    if(board[nr][nc] == '#' || board[nr][nc] == 'B') {
                        q.emplace(nr, nc, t + 1);
                        visited[nr][nc] = true;
                    } else if(isdigit(board[nr][nc])) {
                        if(traffic_state[board[nr][nc] - '0'] == (j & 1)) {
                            q.emplace(nr, nc, t + 1);
                            visited[nr][nc] = true;
                        } else {
                            q.emplace(r, c, t + 1);
                        }
                    }
                }
            }

            for(int i = 0; i < traffic; i++) {
                auto [c, a, b] = traffic_light[i];
                if(--remain_time[i] == 0) {
                    if(traffic_state[i] == 0) {
                        traffic_state[i] = 1;
                        remain_time[i] = b;
                    } else {
                        traffic_state[i] = 0;
                        remain_time[i] = a;
                    }
                }
            }
        }
        cout << "impossible\n";
        EXIT_LOOP2: {}
    }
}