#include <bits/stdc++.h>

using namespace std;

const int MAXR = 3030;
const int MAXRC = 3030 * 3030;

int R, C, H, W, X[MAXRC], Y[MAXRC], S[MAXR][MAXR];

bool compute(int x)
{
    for(int i = x; i <= R*C; i++)
        S[Y[i]][X[i]] += 1;
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            S[i][j] += S[i-1][j] + S[i][j-1] - S[i-1][j-1];
        }
    }

    for(int i = 1; i <= R - H + 1; i++) {
        for(int j = 1; j <= C - W + 1; j++) {
            int r = i + H - 1;
            int c = j + W - 1;
            int s = S[r][c] - S[r][j-1] - S[i-1][c] + S[i-1][j-1];
            if(s <= (H * W) / 2) {
                for(int i = 1; i <= R; i++) for(int j = 1; j <= C; j++) S[i][j] = 0;
                return true;
            }
        }
    }
    for(int i = 1; i <= R; i++) for(int j = 1; j <= C; j++) S[i][j] = 0;
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> R >> C >> H >> W;
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            int a;
            cin >> a;
            Y[a] = i;
            X[a] = j;
        }
    }

    int lo = 1;
    int hi = R * C + 1;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(compute(mid)) hi = mid;
        else lo = mid;
    }
    cout << lo;
}