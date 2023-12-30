#include <bits/stdc++.h>

using namespace std;

const int INF = 98765321;
const int dr[] = {-1, 0, 0, 1};
const int dc[] = {0, -1, 1, 0};

int n, m;
char board[50][50];

int bfs(int sr, int sc, int sd, int er, int ec, int ed)
{
    bool visited[50][50][4] = {};
    queue<tuple<int, int, int, int>> q;
    q.emplace(sr, sc, sd, 0);

    if(0 < sd) visited[sr][sc][sd] = true;

    while(!q.empty())
    {
        auto [r, c, dir, dist] = q.front(); q.pop();
        if(r == er && c == ec && (dir == ed || ed < 0))
        {
            return dist;
        }

        for(int i = 0; i < 4; i++)
        {
            if(i == dir) continue;
            int nr = r + dr[i];
            int nc = c + dc[i];

            if(nr < 0 || n <= nr || nc < 0 || m <= nc || board[r][c] == '#' || visited[nr][nc][i]) continue;

            visited[nr][nc][i] = true;
            q.emplace(nr, nc, i, dist + 1);
        }
    }

    return INF;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    int sr, sc;
    vector<pair<int, int>> cs;
    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < m; c++)
        {
            cin >> board[r][c];
            if(board[r][c] == 'S')
            {
                sr = r;
                sc = c;
            }
            else if(board[r][c] == 'C')
            {
                cs.emplace_back(r, c);
            }
        }
    }

    int ans = INF;
    for(int i = 0; i < 4; i++)
    {
        int dist = bfs(sr, sc, -1, cs[0].first, cs[0].second, i);
        dist += bfs(cs[0].first, cs[0].second, i, cs[1].first, cs[1].second, -1);
        ans = min(ans, dist);
    }

    for(int i = 0; i < 4; i++)
    {
        int dist = bfs(sr, sc, -1, cs[1].first, cs[1].second, i);
        dist += bfs(cs[1].first, cs[1].second, i, cs[0].first, cs[0].second, -1);
        ans = min(ans, dist);
    }

    if(INF <= ans) cout << -1;
    else cout << ans;
}