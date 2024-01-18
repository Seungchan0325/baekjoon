#include <iostream>
#include <queue>
#include <utility>
#include <memory.h>

using namespace std;

using pii = pair<int, int>;

const int dir_x[] = {1, -1, 0, 0};
const int dir_y[] = {0, 0, 1, -1};

int n, m, cheese[102][102], visited[102][102];

bool in_range(int i, int n) { return 0 <= i && i < n; }

int bfs() {
    int deleted=0;
    queue<pii> que;
    que.push({0, 0});
    visited[0][0] = 1;
    memset(visited, 0, sizeof(visited));
    while(!que.empty()) {
        auto top = que.front(); que.pop();

        for(int i=0; i<4; i++) {
            int ny = top.first + dir_y[i];
            int nx = top.second + dir_x[i];

            if(!in_range(ny, n+2) || !in_range(nx, m+2)) continue;
            if(cheese[ny][nx] == 0 && visited[ny][nx] == 0) {
                que.push({ny, nx});
                visited[ny][nx] = 1;
            }
            if(cheese[ny][nx] == 1) {
                cheese[ny][nx] = 0;
                visited[ny][nx] = 1;
                deleted++;
            }
        }
    }

    return deleted;
}

int main() {
    int cheese_num=0, t=1;
    cin>>n>>m;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++) {
            cin>>cheese[i][j];
            if(cheese[i][j] == 1) cheese_num++;
        }
    
    while(true) {
        int result = bfs();
        if(cheese_num - result == 0) {
            cout<<t<<endl;
            cout<<cheese_num<<endl;
            break;
        }
        cheese_num -= result;
        t++;
    }
}