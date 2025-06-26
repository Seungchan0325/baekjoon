#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;
const int inf = 1e9;

struct DSU {
    int N;
    vector<int> root;
    DSU(int _N) : N(_N) {
        root.resize(N+1);
        iota(root.begin(), root.end(), 0);
    }

    void init()
    {
        iota(root.begin(), root.end(), 0);
    }

    int find(int x)
    {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }

    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        root[y] = x;
    }
};

int N, where[MAXN], w[MAXN][MAXN], flow[MAXN][MAXN], par[MAXN], level[MAXN], work[MAXN];
int A, B;

bool bfs()
{
    DSU dsu(N+5);
    queue<int> q;
    for(int i = 1; i <= N+2; i++) par[i] = -1;

    q.push(A);
    level[A] = 1;
    par[A] = A;
    dsu.merge(A+1, A);

    while(!q.empty()) {
        int here = q.front(); q.pop();
        for(int next = dsu.find(1); next <= N+2; next = dsu.find(next+1)) {
            if(par[next] == -1 && w[here][next] - flow[here][next] > 0) {
                level[next] = level[here] + 1;
                par[next] = here;
                dsu.merge(next+1, next);
                q.push(next);
            }
        }
    }

    return par[B] != -1;
}

int dfs(int u, int f)
{
    if(u == B) return f;
    for(int& v = work[u]; v <= N+2; v++) {
        if(level[v] == level[u] + 1 && w[u][v] - flow[u][v] > 0) {
            int df = dfs(v, min(f, w[u][v] - flow[u][v]));
            if(df > 0) {
                flow[u][v] += df;
                flow[v][u] -= df;
                return df;
            }
        }
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) cin >> where[i];
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> w[i][j];
        }
    }

    int zero = true;
    for(int i = 1; i <= N; i++) {
        if(where[i] != 0) {
            zero = false;
            break;
        }
    }
    if(zero) {
        cout << "0";
        return 0;
    }

    A = N+1;
    B = N+2;
    for(int i = 1; i <= N; i++) {
        if(where[i] == 1) w[A][i] = w[i][A] = inf;
        if(where[i] == 2) w[B][i] = w[i][B] = inf;
    }

    int ans = 0;
    while(bfs()) {
        fill(work, work+N+5, 1);
        while(true) {
            int df = dfs(A, inf);
            ans += df;
            if(df == 0) break;
        }
    }
    cout << ans << "\n";

    memset(par, -1, sizeof(par));
    queue<int> q;
    q.push(A);
    par[A] = A;

    vector<int> GA;
    while(!q.empty()) {
        int here = q.front(); q.pop();
        if(here <= N) GA.push_back(here);
        for(int next = 1; next <= N+2; next++) {
            if(par[next] == -1 && w[here][next] - flow[here][next] > 0) {
                par[next] = here;
                q.push(next);
            }
        }
    }

    for(auto i : GA) cout << i << " ";
    cout << "\n";
    for(int i = 1; i <= N; i++) if(find(GA.begin(), GA.end(), i) == GA.end()) cout << i << " ";
    cout << "\n";
}