#include <iostream>
#include <queue>
#include <utility>
#include <memory.h>

#define MAX_SIZE 1000

using namespace std;
using coord = pair<int, int>;

constexpr coord dir[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int w, h;
char map[MAX_SIZE+1][MAX_SIZE+1];
bool visit[MAX_SIZE+1][MAX_SIZE+1];

bool in_range(int x, int n) {
    return 0 <= x && x < n;
}

int bfs() {
    int time=0;
    queue<coord> human, fire;

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(map[i][j] == '@') {
                human.push({i, j});
                map[i][j] = '.';
            }else if(map[i][j] ==  '*') {
                fire.push({i, j});
            }
        }
    }

    while(!human.empty()) {
        time++;
        for(int i=0, fire_size=fire.size(); i < fire_size; i++) {
            auto cur = fire.front(); fire.pop();

            for(int j=0; j<4; j++) {
                coord next = {
                    cur.first + dir[j].first, 
                    cur.second + dir[j].second
                };

                if(!in_range(next.first, h) || !in_range(next.second, w)) continue;
                if(map[next.first][next.second] != '.') continue;

                fire.push(next);
                map[next.first][next.second] = '*';
            }
        }

        for(int i=0, human_size=human.size(); i < human_size; i++) {
            auto cur = human.front(); human.pop();

            for(int j=0; j<4; j++) {
                coord next = {
                    cur.first + dir[j].first,
                    cur.second + dir[j].second
                };

                if(!in_range(next.first, h) || !in_range(next.second, w)) return time;

                if(map[next.first][next.second] != '.'
                    || visit[next.first][next.second]) continue;
                human.push(next);
                visit[next.first][next.second] = true;
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int t;
    cin>>t;
    while(t--) {
        cin>>w>>h;
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                cin>>map[i][j];
            }
        }
        memset(visit, 0, sizeof(visit));

        auto result = bfs();
        if(result == -1) cout << "IMPOSSIBLE" << endl;
        else cout << result << endl;
    }
}