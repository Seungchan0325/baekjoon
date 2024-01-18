#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
const int dx[] = {-1, 0, 0, 1};
const int dy[] = {0, -1, 1, 0};

int n, m;
char board[MAXN][MAXN];
bool visited[2][MAXN][MAXN];

int main()
{
    cin >> n >> m;
    for(int y = 0; y < n; y++)
    {
        for(int x = 0; x < m; x++)
        {
            cin >> board[y][x];
        }
    }

    int distance = -1;
    queue<tuple<int, int, int, int>> que;
    que.emplace(0, 0, 0, 1);
    visited[0][0][0] = visited[1][0][0] = true;
    while(!que.empty())
    {
        auto [x, y, b, d] = que.front();
        que.pop();

        if(x == m - 1 && y == n - 1)
        {
            distance = d;
            break;
        }

        for(int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || m <= nx || ny < 0 || n <= ny || (b == 1 && board[ny][nx] == '1'))
            {
                continue;
            }

            bool flag = false;
            for(int i = 0; i <= b; i++)
            {
                if(visited[i][ny][nx]) flag = true;
            }

            if(flag)
            {
                continue;
            }

            if(board[ny][nx] == '0')
            {
                que.emplace(nx, ny, b, d + 1);
                visited[b][ny][nx] = true;
            }
            else
            {
                que.emplace(nx, ny, b + 1, d + 1);
                visited[b + 1][ny][nx] = true;
            }
        }
    }

    cout << distance;
}