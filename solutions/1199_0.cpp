#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int N, tree[MAXN][MAXN];
int g[MAXN][MAXN];

void update(int t[], int pos, int delta)
{
    while(pos <= N) {
        t[pos] += delta;
        pos += pos & -pos;
    }
}

int query(int t[], int pos)
{
    int ret = 0;
    while(pos > 0) {
        ret += t[pos];
        pos -= pos & -pos;
    }
    return ret;
}

int first(int t[])
{
    int ret = 0;
    for(int p = 10; p >= 0; p--) {
        if(ret + (1<<p) <= N && t[ret+(1<<p)] == 0) ret += (1<<p);
    }
    return ret + 1;
}

void dfs(int u)
{
    while(query(tree[u], N)) {
        int v = first(tree[u]);
        update(tree[u], v, -1);
        update(tree[v], u, -1);
        dfs(v);
    }
    cout << u << " ";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> g[i][j];
            update(tree[i], j, g[i][j]);
        }
    }

    bool is_possible = true;
    for(int i = 1; i <= N; i++) {
        int cnt = 0;
        for(int j = 1; j <= N; j++) {
            cnt += g[i][j];
        }
        if(cnt&1) is_possible = false;
    }

    if(!is_possible) {
        cout << "-1";
        return 0;
    }

    dfs(1);
}