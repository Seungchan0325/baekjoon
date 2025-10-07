#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;
const int mod = 1e9 + 7;

int N, M;
int p[MAXN], v[MAXN], e[MAXN];

int find(int x)
{
    if(p[x] == x) return x;
    return p[x] = find(p[x]);
}

void add_edge(int x, int y)
{
    x = find(x);
    y = find(y);

    if(x == y) {
        e[x]++;
        return;
    }

    p[y] = x;
    v[x] += v[y];
    e[x] += e[y] + 1;
}

int main()
{
    cin >> N >> M;
    fill(v, v+MAXN, 1);
    iota(p, p+MAXN, 0);
    for(int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        add_edge(u, v);
    }
    long long ans = 1;
    for(int i = 1; i <= N; i++) {
        if(i != find(i)) continue;
        if(v[i] == e[i]) {
            ans = 2 * ans % mod;
        } else if(v[i] == e[i] + 1) {
            ans = v[i] * ans % mod;
        } else ans = 0;
    }
    cout << ans << "\n";
}