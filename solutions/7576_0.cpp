#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

using pii = pair<int, int>;

const pii dir[] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int n, m, box[1001][1001];

bool in_range(int i, int n) {
    return 0 <= i && i < n;
}

bool is_done() {
    for(int i=0; i<n; i++)
        if(any_of(&box[i][0], &box[i][m], [](int i){return i == 0;}))
            return false;
    return true;
}

int max_element() {
    int ret = -1;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++) {
            ret = max(ret, box[i][j]);
        }
    return ret;
}

void solve() {
    queue<pii> que;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(box[i][j] == 1)
                que.push({i, j});
    
    while(!que.empty()) {
        auto front = que.front(); que.pop();

        for(int i=0; i<4; i++) {
            int next_y = front.first + dir[i].first;
            int next_x = front.second + dir[i].second;

            if(!in_range(next_y, n) || !in_range(next_x, m))
                continue;
            
            if(box[next_y][next_x] == 0) {
                que.push({next_y, next_x});
                box[next_y][next_x] = box[front.first][front.second]+1;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>m>>n;

    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin>>box[i][j];

    solve();

    if(!is_done()) {
        cout<<-1<<endl;
    } else {
        cout<<max_element()-1<<endl;
    }
}