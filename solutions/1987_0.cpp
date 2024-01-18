#include <iostream>
#include <vector>

using namespace std;

constexpr int dis_y[] = {0, 0, 1, -1},
              dis_x[] = {1, -1, 0, 0};

bool used_alphabet[26] = { false };
int R, C, max_dis;
vector<vector<char>> input;

void dfs(int y, int x, int depth) {
    max_dis = max(max_dis, depth);
    
    for(int i = 0; i < 4; i++) {
        int yy = y + dis_y[i],
            xx = x + dis_x[i];
        
        if(yy < 0 || yy >= R ||
           xx < 0 || xx >= C) continue;

        int idx = input[yy][xx];
        if(used_alphabet[idx] == false) {
            used_alphabet[idx] = true;
            dfs(yy, xx, depth + 1);
            used_alphabet[idx] = false;
        }
    }
}

int main() {
    cin >> R >> C;

    input.resize(R, vector<char>(C));
    for(auto& i : input) {
        for(auto& j : i) {
            cin >> j;
            j -= 'A';
        }
    }
    
    used_alphabet[input[0][0]] = true;
    dfs(0, 0, 1);

    cout << max_dis;
}