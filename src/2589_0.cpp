#include <iostream>
#include <queue>
#include <utility>
#include <memory.h>

using namespace std;

using pii = pair<int, int>;

const pii dir[] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int n, m, map[50][50], visited[50][50];

bool in_range(int i, int n) {
    return 0 <= i && i < n;
}

int bfs(int y, int x) {
    int distance = 0;
    queue<pair<int, int>> que;
    memset(visited, 0, sizeof(visited));
    que.push({y, x});
    visited[y][x] = true;

    while(!que.empty()) {
        int que_size = que.size();
        for(int i=0; i<que_size; i++) {
            auto cur = que.front(); que.pop();

            for(int j=0; j<4; j++) {
                int ny = cur.first+dir[j].first;
                int nx = cur.second+dir[j].second;

                if(!in_range(ny, n) || !in_range(nx, m)) continue;
                if(map[ny][nx] == 0) continue;
                if(visited[ny][nx]) continue;

                que.push({ny, nx});
                visited[ny][nx] = true;
            }
        }
        distance++;
    }
    return distance-1;
}

int main() {
    cin>>n>>m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++) {
            char input;
            cin>>input;
            if(input == 'L')
                map[i][j] = 1;
        }
    
    int result = -1;

    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(map[i][j] == 1)
                result = max(bfs(i, j), result);
    
    cout<<result<<endl;
}