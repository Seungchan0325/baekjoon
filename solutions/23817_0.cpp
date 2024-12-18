#include <bits/stdc++.h>

using namespace std;

// #define int long long

const int MAXN = 1005;

const int di[] = {0, 0, 1, -1};
const int dj[] = {1, -1, 0, 0};

int N, M, cache[1<<21][21];
char m[MAXN][MAXN];
vector<vector<int>> d;
vector<pair<int, int>> Ks;

vector<vector<int>> bfs(int i, int j)
{
    vector<vector<bool>> vst(N+1, vector<bool>(M+1, false));
    vector<vector<int>> dist(N+1, vector<int>(M+1, 1e9));

    queue<pair<int, int>> q;
    dist[i][j] = 0;
    vst[i][j] = true;
    q.emplace(i, j);

    while(!q.empty()) {
        auto [i, j] = q.front(); q.pop();
        for(int k = 0; k < 4; k++) {
            int ni = i + di[k];
            int nj = j + dj[k];

            if(ni < 1 || ni > N || nj < 1 || nj > M || vst[ni][nj] || m[ni][nj] == 'X') continue;

            vst[ni][nj] = true;
            dist[ni][nj] = dist[i][j] + 1;
            q.emplace(ni, nj);
        }
    }
    return dist;
}

int dp(int bit, int pos)
{
    if(bit == 1 && pos == 0) return 0;
    else if(bit == 0) return 1e9;

    int& ret = cache[bit][pos];
    if(ret != -1) return ret;

    ret = 1e9;
    for(int j = 0; j < Ks.size(); j++) {
        if(pos == j) continue;
        if(bit&(1<<j)) {
            ret = min(ret, dp(bit^(1<<pos), j) + d[j][pos]);
        }
    }

    return ret;
}

signed main()
{
    int _idx = 0;
    cin >> N >> M;
    Ks.push_back({0, 0});
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> m[i][j];
            if(m[i][j] == 'S') {
                Ks[0].first = i;
                Ks[0].second = j;
            } else if(m[i][j] == 'K') {
                Ks.emplace_back(i, j);
            }
        }
    }

    d.resize(Ks.size());
    for(int i = 0; i < Ks.size(); i++) {
        auto dist = bfs(Ks[i].first, Ks[i].second);
        for(int j = 0; j < Ks.size(); j++) {
            d[i].push_back(dist[Ks[j].first][Ks[j].second]);
        }
    }

    memset(cache, -1, sizeof(cache));
    int ans = 1e9;
    for(int bit = 0; bit < (1<<(Ks.size())); bit++) {
        if(__builtin_popcount(bit) == 6) {
            for(int pos = 0; pos < Ks.size(); pos++) {
                if(bit&(1<<pos)) {
                    ans = min(ans, dp(bit, pos));
                }
            }
        }
    }
    if(ans >= 1e9) cout << "-1";
    else cout << ans;
}