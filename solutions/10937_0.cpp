#include <bits/stdc++.h>

using namespace std;

const int MAXN = 11;
const int price[][4] = {
    {100, 70, 40, 0},
    {70, 50, 30, 0},
    {40, 30, 20, 0},
    {0, 0, 0, 0},
};

int N, board[MAXN+1][MAXN+1], cache[1<<(MAXN+1)][MAXN][MAXN];
int mask;

int get_max_price(int taken, int x, int y)
{
    int& ret = cache[taken][x][y];
    if(ret != -1) return ret;
    if(x == N) return ret = 0;
    if(y == N) return get_max_price(taken, x+1, 0);

    if(~taken & (1<<N)) {
        if(x < N-1 && (~taken & 1)) {
            int cand = get_max_price(((taken|1)<<1)&mask, x, y+1) + price[board[y][x]][board[y][x+1]];
            ret = max(cand, ret);
        }
        if(y < N-1 && (~taken & (1<<(N-1)))) {
            int cand = get_max_price((taken<<2)&mask, x, y+2) + price[board[y][x]][board[y+1][x]];
            ret = max(cand, ret);
        }
    }
    int cand = get_max_price((taken<<1)&mask, x, y+1);
    ret = max(cand, ret);

    return ret;
}

int to_idx[256];

int main()
{
    to_idx['A'] = 0;
    to_idx['B'] = 1;
    to_idx['C'] = 2;
    to_idx['F'] = 3;
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            char c;
            cin >> c;
            board[i][j] = to_idx[c];
        }
    }

    mask = (1<<(N+1)) - 1;
    memset(cache, -1, sizeof(cache));
    int result = get_max_price(0, 0, 0);
    cout << result;
}