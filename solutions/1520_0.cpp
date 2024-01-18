#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;

const int dr[] = {0, 0, 1, -1};
const int dc[] = {-1, 1, 0, 0};

int n, m, heights[MAXN][MAXN], dp[MAXN][MAXN];

int dfs(int r, int c)
{
    if(r == n-1 && c == m-1)
    {
        return 1;
    }
    int& ret = dp[r][c];
    if(ret != -1)
    {
        return ret;
    }

    ret = 0;
    for(int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(nr < 0 || n <= nr || nc < 0 || m <= nc || heights[r][c] <= heights[nr][nc])
        {
            continue;
        }

        ret += dfs(nr, nc);
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> heights[i][j];
        }
    }

    memset(dp, -1, sizeof(dp));
    int result = dfs(0, 0);
    cout << result;
}