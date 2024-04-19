#include <bits/stdc++.h>

using namespace std;

const int MAXN = 15;

const int price[][5] = {
    {10, 8, 7, 5, 1},
    {8, 6, 4, 3, 1},
    {7, 4, 3, 2, 1},
    {5, 3, 2, 2, 1},
    {1, 1, 1, 1, 0},
};

int N, M, grade[MAXN][MAXN];
int toidx[127];
int cache[1<<MAXN][MAXN][MAXN];

int dp(int taken, int i, int j)
{
    if(i == N) return 0;
    if(j == M) return dp(taken, i + 1, 0);

    int& ret = cache[taken][i][j];
    if(ret != -1) return ret;

    ret = dp(taken>>1, i, j + 1);
    if(~taken & 1) {
        if(j < M - 1 && !(taken & 2)) {
            int cand = dp((taken>>1)|1, i, j+1) + price[grade[i][j]][grade[i][j+1]];
            ret = max(cand, ret);
        }

        if(i < N - 1 && !(taken & (1<<M))) {
            int cand = dp(((taken|(1<<M))>>1), i, j+1) + price[grade[i][j]][grade[i+1][j]];
            ret = max(cand, ret);
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    toidx['A'] = 0;
    toidx['B'] = 1;
    toidx['C'] = 2;
    toidx['D'] = 3;
    toidx['F'] = 4;
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            char g;
            cin >> g;
            grade[i][j] = toidx[g];
        }
    }

    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0, 0);
    cout << result;
}