#include <iostream>
#include <limits>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

int n, m, ans = numeric_limits<int>::max();
vector<vector<int>> map;
vector<vector<bool>> visited;

constexpr int dir_y[] = {1, -1, 0, 0};
constexpr int dir_x[] = {0, 0, 1, -1};

void bfs() {
    queue<pair<pair<int, int>, int>> que;
    que.push({{0, 0}, 1});
    while(!que.empty()) {
        auto f = que.front(); que.pop();
        int y = f.first.first,
            x = f.first.second,
            depth = f.second;

        if(y == n - 1 && x == m - 1) {
            ans = depth;
            break;
        }

        for(int i = 0; i < 4; i++) {
            int yy = y + dir_y[i], xx = x + dir_x[i];

            if(yy >= n || xx >= m ||
               yy < 0 || xx < 0) continue;

            if(map[yy][xx] == 1 && visited[yy][xx] == 0) {
                visited[yy][xx] = true;
                que.push({{yy, xx}, depth + 1});
            }
        }
    }
}

int main() {
    cin >> n >> m;
    map.resize(n, vector<int>(m));
    visited.resize(n, vector<bool>(m));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%1d", &map[i][j]);

    bfs();

    cout << ans << endl;
}