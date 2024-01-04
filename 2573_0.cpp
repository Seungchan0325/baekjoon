#include <iostream>
#include <vector>

using namespace std;

constexpr int dir_x[] = {1, -1, 0, 0},
              dir_y[] = {0, 0, 1, -1};

int R, C;
vector<vector<int>> input;
vector<vector<bool>> visited;

void dfs(int y, int x) {
    visited[y][x] = true;

    for(int i = 0; i < 4; i++) {
        int yy = y + dir_y[i],
            xx = x + dir_x[i];

        if(yy < 0 || yy >=R ||
           xx < 0 || xx >=C) continue;

        if(visited[yy][xx] == false && input[yy][xx] != 0)
            dfs(yy, xx);
    }
}

int count_lump() {
    visited = vector<vector<bool>>(R, vector<bool>(C));
    int count = 0;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            if(visited[i][j] == false && input[i][j] != 0) {
                dfs(i, j);
                count++;
            }
        }
    }
    visited = vector<vector<bool>>(R, vector<bool>(C));
    return count;
}

bool next_year() {
    bool flag = false;
    vector<vector<bool>> visited(R, vector<bool>(C));
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            if(input[i][j] == 0) continue;
            flag = true;
            visited[i][j] = true;
            for(int k = 0; k < 4; k++) {
                int yy = dir_y[k] + i,
                    xx = dir_x[k] + j;

                if(yy < 0 || yy >= R ||
                   xx < 0 || xx >= C) continue;

                if(input[yy][xx] == 0 && visited[yy][xx] == false) input[i][j]--;
            }

            if(input[i][j] < 0) input[i][j] = 0;
        }
    }
    return flag;
}

int main() {
    cin >> R >> C;

    input.resize(R, vector<int>(C));
    for(auto& i : input)
        for(auto& j : i)
            cin >> j;

    int year = 0, first_cnt = count_lump(), cnt;
    while(true) {
        year++;
        if(next_year() == false) break;

        cnt = count_lump();
        if(cnt >= 2)
            break;
    }

    if(cnt < 2 || cnt == first_cnt)
        cout << 0 << endl;
    else
        cout << year << endl;
}