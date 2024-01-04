#include <iostream>
#include <vector>

using namespace std;

constexpr int dir_y[] = {0, 0, 1, -1},
              dir_x[] = {1, -1, 0, 0};

enum {
    out_air,
    cheese,
};

int N, M;
vector<vector<int>> input;
vector<vector<bool>> visited;

void dfs(int y, int x, int val) {
    input[y][x] = val;
    visited[y][x] = true;

    for(int i = 0; i < 4; i++) {
        int yy = y + dir_y[i],
            xx = x + dir_x[i];

        if(yy < 0 || yy >= N ||
           xx < 0 || xx >= M) continue;
        
        if(visited[yy][xx] == false && input[yy][xx] != 1)
            dfs(yy, xx, val);
    }
}

void grouping() {
    visited = vector<vector<bool>>(N, vector<bool>(M));
    int val = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(visited[i][j] == false && input[i][j] == 0) {
                dfs(i, j, val);
                val = 3;
            }
        }
    }
}

bool next_hour() {
    bool flag = false;
    grouping();
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(input[i][j] != 1) continue;
            flag = true;
            int cnt = 0;
            for(int k = 0; k < 4; k++) {
                int yy = i + dir_y[k],
                    xx = j + dir_x[k];
                
                if(yy < 0 || yy >= N ||
                   xx < 0 || xx >= M) continue;
                
                if(input[yy][xx] == out_air) cnt++;
            }
            if(cnt >= 2) input[i][j] = 3;
        }
    }

    // cout << endl;
    // for(auto& i : input) {
    //     for(auto& j : i) {
    //         cout << j << " ";
    //     }
    //     cout << endl;
    // }

    return flag;
}

int main() {
    int hour = 0;
    cin >> N >> M;

    input.resize(N, vector<int>(M));
    for(auto& i : input)
        for(auto& j : i)
            cin >> j;

    while(next_hour()) hour++;

    cout << hour << endl;
}