#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;
vector<vector<int>> map;
vector<int> answer;
constexpr int dir[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void grouping(int x, int y, int val) {
    answer[val-1]++;
    map[y][x] = val;
    for(int i = 0; i < 4; i++) {
        if(y+dir[i][0] < 0 || x+dir[i][1] < 0 || x+dir[i][1] >= n || y+dir[i][0] >= n) continue;
        if(map[y+dir[i][0]][x+dir[i][1]] == 0)
            grouping(x+dir[i][1], y+dir[i][0], val);
    }
}

int main() {
    cin >> n;

    map.resize(n);
    for(auto& i : map)
        i.resize(n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%1d", &map[i][j]);
            map[i][j]--;
        }
    }
    int val = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(map[i][j] == 0) {
                answer.push_back(0);
                grouping(j, i, val);
                val++;
            }
        }
    }
    sort(answer.begin(), answer.end());
    cout << answer.size() << "\n";
    for(auto i : answer) {
        cout << i << "\n";
    }
}