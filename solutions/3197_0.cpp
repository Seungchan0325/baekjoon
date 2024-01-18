#include <iostream>
#include <utility>
#include <queue>

using namespace std;

struct rc_t {
    int r;
    int c;

    bool operator==(const rc_t& other) {
        return r == other.r && c == other.c;
    }

    rc_t operator+(const rc_t& other) {
        return {r + other.r, c + other.c};
    }
};

const int RMAX = 1500, CMAX = 1500;
const rc_t drc[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int R, C;
rc_t swans[2];
rc_t parents[RMAX][CMAX];
char map[RMAX][CMAX];
bool visit[RMAX][CMAX];

bool in_range(int st, int i, int en) { return st <= i && i < en; }

rc_t find(rc_t rc) {
    if(parents[rc.r][rc.c] == rc) return rc;
    return parents[rc.r][rc.c] = find(parents[rc.r][rc.c]);
}

void Union(rc_t rc1, rc_t rc2) {
    rc1 = find(rc1);
    rc2 = find(rc2);

    parents[rc2.r][rc2.c] = rc1;
}

void dfs(rc_t rc) {
    visit[rc.r][rc.c] = true;

    for(int d=0; d<4; d++) {
        rc_t nrc = rc + drc[d];
        if(!in_range(0, nrc.r, R) || !in_range(0, nrc.c, C)) continue;
        if(map[nrc.r][nrc.c] == 'X' || visit[nrc.r][nrc.c]) continue;

        Union(rc, nrc);
        dfs(nrc);
    }
}

int bfs() {
    int ret = 0;
    queue<rc_t> q;

    for(int r=0; r<R; r++)
        for(int c=0; c<C; c++)
            if(map[r][c] != 'X')
                q.push({r, c});
    
    while(true) {
        ret++;
        int n = q.size();
        for(int i=0; i<n; i++) {
            for(int d=0; d<4; d++) {
                rc_t nrc = q.front() + drc[d];
                if(!in_range(0, nrc.r, R) || !in_range(0, nrc.c, C)) continue;
                if(visit[nrc.r][nrc.c]) continue;

                visit[nrc.r][nrc.c] = true;
                q.push(nrc);
                for(int dd=0; dd<4; dd++) {
                    rc_t nnrc = nrc + drc[dd];
                    if(!in_range(0, nnrc.r, R) || !in_range(0, nnrc.c, C)) continue;
                    if(!visit[nnrc.r][nnrc.c]) continue;

                    Union(nrc, nnrc);
                }
            }
            q.pop();
        }

        rc_t s1 = find(swans[0]);
        rc_t s2 = find(swans[1]);
        if(s1 == s2)
            break;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>R>>C;

    int cnt = 0;
    for(int r=0; r<R; r++)
        for(int c=0; c<C; c++) {
            cin>>map[r][c];
            if(map[r][c] == 'L') {
                swans[cnt++] = {r, c};
            }
        }
    
    //parents initialize
    {
        for(int r=0; r<R; r++)
            for(int c=0; c<C; c++) {
                parents[r][c] = {r, c};
            }
    }

    for(int r=0; r<R; r++)
        for(int c=0; c<C; c++)
            if(map[r][c] != 'X')
                dfs({r, c});
    
    int result = bfs();

    cout<<result;
}