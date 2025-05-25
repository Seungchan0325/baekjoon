#include <bits/stdc++.h>

using namespace std;

const int dx[] = {-1, 0, 0, 1};
const int dy[] = {0, -1, 1, 0};

const int score[][5] = {
    {10, 8, 7, 5, 1},
    {8, 6, 4, 3, 1},
    {7, 4, 3, 2, 1},
    {5, 3, 2, 2, 1},
    {1, 1, 1, 1, 0},
};

int n, m, id[55][55], p, s, e, c2i[256];
int board[55][55];
int cost[3000][3000], flow[3000][3000], cap[3000][3000], par[3000], inQ[3000], dist[3000];
vector<int> g[3000];

void add_edge(int i, int j, int c, int w)
{
    g[i].push_back(j);
    g[j].push_back(i);
    cap[i][j] = c;
    cost[i][j] = w;
    cost[j][i] = -w;
}

void spfa()
{
    memset(par, -1, sizeof(par));
    memset(inQ, 0, sizeof(inQ));
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    while(!q.empty()) {
        int now = q.front(); q.pop();
        inQ[now] = false;
        for(auto nxt : g[now]) {
            if(cap[now][nxt] - flow[now][nxt] > 0 && dist[now] + cost[now][nxt] < dist[nxt]) {
                dist[nxt] = dist[now] + cost[now][nxt];
                par[nxt] = now;
                if(!inQ[nxt]) {
                    q.push(nxt);
                    inQ[nxt] = true;
                }
            }
        }
    }
}

int mcmf()
{
    // int mx = 0;
    int ans = 0;
    while(true) {
        spfa();
        if(par[e] == -1) break;
        int f = 1e9;
        for(int i = e; par[i] != -1; i = par[i]) {
            f = min(f, cap[par[i]][i] - flow[par[i]][i]);
        }
        for(int i = e; par[i] != -1; i = par[i]) {
            flow[par[i]][i] += f;
            flow[i][par[i]] -= f;
            ans += cost[par[i]][i] * f;
        }
        // mx = min(ans, mx);
    }
    return ans;
}

int main()
{
    c2i['A'] = 0;
    c2i['B'] = 1;
    c2i['C'] = 2;
    c2i['D'] = 3;
    c2i['F'] = 4;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            board[i][j] = c2i[c];
        }
    }

    s = p++;
    e = p++;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            id[i][j] = p++;
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if((i^j)&1) {
                for(int k = 0; k < 4; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if(ni < 1 || ni > n || nj < 1 || nj > m) continue;
                    add_edge(id[i][j], id[ni][nj], 1, -score[board[ni][nj]][board[i][j]]);
                }
                add_edge(s, id[i][j], 1, 0);
                add_edge(id[i][j], e, 1, 0);
            } else {
                add_edge(id[i][j], e, 1, 0);
            }
        }
    }

    int ans = -mcmf();
    cout << ans;
}