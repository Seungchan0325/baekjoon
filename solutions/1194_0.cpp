#include <bits/stdc++.h>

using namespace std;

const int dr[] = {0, 0, -1, 1};
const int dc[] = {-1, 1, 0, 0};

int n, m;
char arr[50][50];
bool visited[50][50][4][1<<6];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    int sr, sc;
    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < m; c++)
        {
            cin >> arr[r][c];
            if(arr[r][c] == '0')
            {
                sr = r;
                sc = c;
            }
        }
    }

    // r, c, dir, keys, dist
    queue<tuple<int, int, int, int, int>> q;
    q.emplace(sr, sc, -1, 0, 0);

    while(!q.empty())
    {
        auto [r, c, dir, keys, dist] = q.front(); q.pop();

        if(arr[r][c] == '1')
        {
            cout << dist;
            return 0;
        }

        for(int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if(nr < 0 || n <= nr || nc < 0 || m <= nc || visited[nr][nc][i][keys])
            {
                continue;
            }

            char c = arr[nr][nc];

            int nkeys = keys;
            if(c == '#')
            {
                continue;
            }
            else if('a' <= c && c <= 'f')
            {
                nkeys |= 1<<(c-'a');
            }
            else if('A' <= c && c <= 'F' && !(keys & 1<<(c-'A')))
            {
                continue;
            }
            visited[nr][nc][i][nkeys] = true;
            q.emplace(nr, nc, i, nkeys, dist + 1);
        }
    }

    cout << "-1";
}