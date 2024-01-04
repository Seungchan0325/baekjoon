#include <iostream>
#include <memory.h>

using namespace std;

int n, m, max_id=0;
int id_cache[1000][1000], visited[1000][1000];
char map[1000][1000];

int dir_y(char c) {
    switch(c) {
        case 'N': return -1;
        case 'S': return 1;
        default: return 0;
    }
}

int dir_x(char c) {
    switch(c) {
        case 'W': return -1;
        case 'E': return 1;
        default: return 0;
    }
}

int get_path_id(int y, int x) {
    int& ret = id_cache[y][x];
    if(ret != -1) return ret;

    //visit했는데 ret이 설정되지 않은 경우 -> 사이클
    if(visited[y][x]) return ++max_id;

    visited[y][x] = true;

    ret = get_path_id(y+dir_y(map[y][x]), x+dir_x(map[y][x]));
    
    return ret;
}

int main() {
    memset(id_cache, -1, sizeof(id_cache));
    cin>>n>>m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin>>map[i][j];

    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            get_path_id(i, j);
    
    cout<<max_id<<endl;
}