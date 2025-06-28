#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 500;
const ll inf = 1e18;

int n, m, sum, num[MAXN], lim[MAXN], c[MAXN][MAXN], f[MAXN][MAXN], par[MAXN], lev[MAXN], work[MAXN];
ll w[MAXN][MAXN];
int s = 0, e = 1;

bool bfs()
{
    memset(lev, -1, sizeof(lev));
    queue<int> q;
    q.push(s);
    lev[s] = 0;

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v = s; v <= (n<<1|1); v++) {
            if(lev[v] == -1 && c[u][v] - f[u][v] > 0) {
                lev[v] = lev[u] + 1;
                q.push(v);
            }
        }
    }

    return lev[e] != -1;
}

int dfs(int u, int flow)
{
    if(u == e) return flow;
    for(int& v = work[u]; v <= (n<<1|1); v++) {
        if(lev[v] == lev[u] + 1 && c[u][v] - f[u][v] > 0) {
            int df = dfs(v, min(flow, c[u][v] - f[u][v]));
            if(df > 0) {
                f[u][v] += df;
                f[v][u] -= df;
                return df;
            }
        }
    }
    return 0;
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> num[i] >> lim[i], sum += num[i];
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) w[i][j] = inf;
    for(int i = 1; i <= n; i++) w[i][i] = 0;
    for(int i = 1; i <= m; i++) {
        int u, v; ll _w;
        cin >> u >> v >> _w;
        w[u][v] = w[v][u] = min(w[u][v], _w);
    }

    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        int in = i<<1;
        int out = i<<1|1;
        c[in][out] = 1e9;
        c[s][in] = num[i];
        c[out][e] = lim[i];
    }

    vector<tuple<ll, int, int>> e;
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            e.emplace_back(w[i][j], i, j);
        }
    }
    sort(e.begin(), e.end());

    int ans = 0;
    for(auto [_w, i, j] : e) {
        int iIn = i<<1;
        int iOut = i<<1|1;
        int jIn = j<<1;
        int jOut = j<<1|1;
        c[iIn][jOut] = c[jIn][iOut] = 1e9;
        while(bfs()) {
            memset(work, 0, sizeof(work));
            while(true) {
                int df = dfs(s, 1e9);
                ans += df;
                if(df <= 0) break;
            }
        }
        if(ans == sum) {
            if(_w >= inf) cout << "-1\n";
            else cout << _w << "\n";
            return 0;
        }
    }
    cout << "-1\n";
}