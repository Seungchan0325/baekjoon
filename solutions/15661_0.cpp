#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 20;

int team[MAX_N], ans=987654321;
int N, S[MAX_N][MAX_N];

int team_diff() {
    int start, link;
    start = link = 0;

    for(int i=0; i<N; i++) {
        int& cur = team[i] ? start : link;
        for(int j=i+1; j<N; j++) {
            if(team[i] != team[j]) continue;
            cur += S[i][j] + S[j][i];
        }
    }

    return abs(start - link);
}

void f(int idx) {
    if(idx >= N) {
        int cnt = count(team, team+N, 1);
        if(cnt < 2 || N-cnt < 2) return;
        ans = min(team_diff(), ans);
        return;
    }

    f(idx+1);
    team[idx] = true;
    f(idx+1);
    team[idx] = false;
}

int main() {
    scanf("%d", &N);
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            scanf("%d", &S[i][j]);
        
    f(0);
    printf("%d\n", ans);
}