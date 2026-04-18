#include <bits/stdc++.h>
#include <queue>

using namespace std;

const int MAXN = 101010;

int n, c[MAXN], d[MAXN], last[MAXN], nxt[MAXN], uf[MAXN];
double p[MAXN], e[MAXN];

int find(int x)
{
    if(uf[x] == x) return x;
    return uf[x] = find(uf[x]);
}

void mrg(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    uf[y] = x;
    nxt[last[x]] = y;
    last[x] = last[y];
    e[x] = e[x] + p[x] * e[y];
    p[x] *= p[y];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> c[i] >> p[i] >> d[i];
    }

    priority_queue<pair<double, int>> pq;
    for(int i = 1; i <= n; i++) {
        uf[i] = i;
        e[i] = c[i];
        last[i] = i;
        pq.push({-(e[i] / (1-p[i])), i});
    }
    while(!pq.empty()) {
        int u = pq.top().second; pq.pop();
        if(find(u) != u) continue;
        mrg(d[u], u);
        int q = find(u);
        if(q != 0) {
            pq.push({-(e[q] / (1-p[q])), q});
        }
    }
    for(int i = 0, j = nxt[0]; i < n; i++, j = nxt[j]) {
        cout << j << "\n";
    }
}
