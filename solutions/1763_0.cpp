#include <bits/stdc++.h>
#include <queue>

using namespace std;

using ll = long long;

const int MAXN = 1010;

ll N, R, C[MAXN], X[MAXN], Y[MAXN], P[MAXN], uf[MAXN];

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
    Y[x] += Y[y] + X[x] * C[y];
    C[x] += C[y];
    X[x] += X[y];
}

int main()
{
    cin >> N >> R;
    for(int i = 1; i <= N; i++) cin >> C[i];
    for(int i = 1; i < N; i++) {
        int u, v; cin >> u >> v;
        P[v] = u;
    }

    for(int i = 1; i <= N; i++) {
        uf[i] = i;
        X[i] = 1;
        Y[i] = C[i];
    }

    for(int i = 1; i < N; i++) {
        int best = -1;
        for(int j = 1; j <= N; j++) {
            if(j == R || find(j) != j) continue;
            if(best < 0 || C[j] * X[best] > C[best] * X[j]) best = j;
        }
        mrg(P[best], best);
    }

    cout << Y[R] << "\n";
}
