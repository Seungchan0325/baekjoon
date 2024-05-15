#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
const int INF = 987654321;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int m, n, cache[2][MAXN][MAXN];
char board[MAXN][MAXN];

int f(int d, int i, int j)
{
    if(i == m && j == 1) {
        if(board[i][j] == '*' || board[i][j] == '.') return 0;
        return board[i][j] - '0';
    }
    int& ret = cache[d][i][j];
    if(ret != -1) return ret;

    ret = -INF;
    if(d == 0 && 1 < i && board[i-1][j] != '*') {
        ret = max(f(0, i-1, j), ret);
    }
    if(d == 1 && i < m && board[i+1][j] != '*') {
        ret = max(f(1, i+1, j), ret);
    }

    if(1 < j && board[i][j-1] != '*') {
        ret = max({f(0, i, j-1), f(1, i, j-1), ret});
    }

    if('0' <= board[i][j] && board[i][j] <= '9') {
        ret += board[i][j] - '0';
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    while(true) {
        cin >> m >> n;
        if(m == 0 && n == 0) break;
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                cin >> board[i][j];
            }
        }

        memset(cache, -1, sizeof(cache));
        int ans = max(f(0, m, n), f(1, m, n));
        cout << ans << "\n";
    }
}