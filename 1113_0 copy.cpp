#include <bits/stdc++.h>

using namespace std;

const int MAXNM = 55;
const int dr[] = {0, 0, -1, 1};
const int dc[] = {-1, 1, 0, 0};

int n, m, board[MAXNM][MAXNM];
bool visited[MAXNM][MAXNM];

bool DFS(int r, int c, int water)
{
    visited[r][c] = true;

    if(r == 0 || r == n - 1 || c == 0 || c == m - 1)
    {
        return true;
    }

    for(int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if(visited[nr][nc] || water <= board[nr][nc])
        {
            continue;
        }

        if(DFS(nr, nc, water))
        {
            return true;
        }
    }

    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < m; c++)
        {
            char ch;
            cin >> ch;
            board[r][c] = ch - '0';
        }
    }

    int ans = 0;
    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < m; c++)
        {
            for(int water = 9; water > board[r][c]; water--)
            {
                memset(visited, 0, sizeof(visited));
                if(!DFS(r, c, water))
                {
                    ans += water - board[r][c];
                    break;
                }
            }
        }
    }

    cout << ans;
}