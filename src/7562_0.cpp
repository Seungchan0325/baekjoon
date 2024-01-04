#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>

using namespace std;
using coord = pair<int, int>;

constexpr coord dir[] {
    {+1, +2},
    {-1, +2},
    {+1, -2},
    {-1, -2},
    {+2, +1},
    {-2, +1},
    {+2, -1},
    {-2, -1},
};

inline coord add_coord(coord a, coord b) {
    return coord(a.first + b.first, a.second + b.second);
}

inline bool in_range(int n, int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

void solve() {
    int size;
    coord src, dst;

    cin >> size;
    cin >> src.first >> src.second;
    cin >> dst.first >> dst.second;

    queue<coord> q;
    vector<vector<bool>> visited(size, vector<bool>(size));
    vector<vector<int>> arr(size, vector<int>(size));

    q.push(src);
    visited[src.first][src.second] = true;
    
    while(!q.empty()) {
        auto cur = q.front(); q.pop();

        if(cur == dst) {
            cout << arr[cur.first][cur.second] << "\n";
            break;
        }

        for(int i = 0; i < 8; i++) {
            auto next = add_coord(cur, dir[i]);
            
            if(in_range(size, next.first, next.second)) {
                if(!visited[next.first][next.second]) {
                    visited[next.first][next.second] = true;
                    arr[next.first][next.second] = arr[cur.first][cur.second] + 1;
                    q.push(next);
                }
            }
        }
    }
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}