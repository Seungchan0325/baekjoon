#include <iostream>
#include <queue>

using namespace std;

struct pos_t {
    int x;
    int y;
    int d;
    int ops = 0;
};

bool in_range(int a, int n) { return 0 <= a && a < n; }

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
const int dr[4] = {2, 3, 1, 0};
const int dl[4] = {3, 2, 0, 1};
int ans, n, m, mat[100][100];
bool visit[100][100][4];
pos_t s, e;

int main() {
    cin>>n>>m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin>>mat[i][j];
    cin>>s.y>>s.x>>s.d;
    cin>>e.y>>e.x>>e.d;
    s.x--; s.y--; s.d--;
    e.x--; e.y--; e.d--;

    queue<pos_t> q;
    q.push(s);
    visit[s.y][s.x][s.d] = true;
    while(!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int d = q.front().d;
        int ops = q.front().ops;
        q.pop();

        if(e.x == x && e.y == y && e.d == d) {
            ans = ops;
            break;
        }

        int nx = x, ny = y;
        for(int i=0; i<3; i++) {
            nx += dx[d];
            ny += dy[d];
            
            if(!in_range(nx, m) || !in_range(ny, n) || mat[ny][nx]) break;
            if(visit[ny][nx][d]) continue;
            q.push({nx, ny, d, ops + 1});
            visit[ny][nx][d] = true;
        }

        int nd = dr[d];
        if(!visit[y][x][nd]) {
            q.push({x, y, nd, ops + 1});
            visit[y][x][nd] = true;
        }

        nd = dl[d];
        if(!visit[y][x][nd]) {
            q.push({x, y, nd, ops + 1});
            visit[y][x][nd] = true;
        }
    }

    cout<<ans<<"\n";
}