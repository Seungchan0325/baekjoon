#include <iostream>
#include <queue>

using namespace std;

bool _in_range(int i, int n) {
    return 0 <= i && i < n;
}

struct Coord {
    Coord(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {};
    int x, y, z;
    Coord operator+(const Coord& other) {
        return Coord(x+other.x, y+other.y, z+other.z);
    }

    bool in_range(int x_lim, int y_lim, int z_lim) {
        return _in_range(x, x_lim) && _in_range(y, y_lim) && _in_range(z, z_lim);
    }
};

const Coord dir[6] = {
    Coord(1, 0, 0),
    Coord(0, 1, 0),
    Coord(0, 0, 1),
    Coord(-1, 0, 0),
    Coord(0, -1, 0),
    Coord(0, 0, -1),
};

int h, n, m, box[100][100][100];

int find_answer() {
    int ret = -1;
    for(int i=0; i<h; i++)
        for(int j=0; j<n; j++)
            for(int k=0; k<m; k++) {
                if(box[i][j][k] == 0) return -1;
                ret = max(box[i][j][k], ret);
            }
    return ret-1;
}

void bfs() {
    queue<Coord> que;
    for(int i=0; i<h; i++)
        for(int j=0; j<n; j++)
            for(int k=0; k<m; k++)
                if(box[i][j][k] == 1)
                    que.push({i, j, k});
    
    while(!que.empty()) {
        auto front = que.front(); que.pop();

        for(int i=0; i<6; i++) {
            auto next = front + dir[i];

            if(!next.in_range(h, n, m))
                continue;
            
            if(box[next.x][next.y][next.z] == 0) {
                que.push(next);
                box[next.x][next.y][next.z] = box[front.x][front.y][front.z] + 1;
            }
        }
    }
}

int main() {
    cin>>m>>n>>h;

    for(int i=0; i<h; i++)
        for(int j=0; j<n; j++)
            for(int k=0; k<m; k++)
                cin>>box[i][j][k];
    
    bfs();

    int result = find_answer();

    cout<<result<<endl;
}