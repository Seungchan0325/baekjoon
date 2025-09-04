#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;
const int MAXM = MAXN * MAXN;
const int INF = 1e9;

int N, M, U[MAXM], V[MAXM], G[MAXN][MAXN], D[MAXN][MAXN], ans[MAXM];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        cin >> U[i] >> V[i];
        G[U[i]][V[i]] = G[V[i]][U[i]] = 1;
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            D[i][j] = INF;
        }
    }
    for(int i = 1; i <= N; i++) D[i][i] = 0;
    for(int i = 1; i <= M; i++) {
        D[U[i]][V[i]] = D[V[i]][U[i]] = 1;
    }

    for(int k = 1; k <= N; k++) {
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }

    auto print = [&]() {
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                cout << D[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    };

    int sum = 0;
    for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++) sum += D[i][j];
    // print();
    for(int i = M; i >= 1; i--) {
        ans[i] = sum;
        if(D[U[i]][V[i]] == 0) continue;
        for(int j = 1; j <= N; j++) {
            for(int k = 1; k <= N; k++) {
                if(D[j][U[i]] + D[V[i]][k] < D[j][k]) {
                    sum += D[j][U[i]] + D[V[i]][k] - D[j][k];
                    D[j][k] = D[j][U[i]] + D[V[i]][k];
                }
                if(D[j][V[i]] + D[U[i]][k] < D[j][k]) {
                    sum += D[j][V[i]] + D[U[i]][k] - D[j][k];
                    D[j][k] = D[j][V[i]] + D[U[i]][k];
                }
            }
        }
        if(sum == 0) break;
        // print();
    }

    for(int i = 1; i <= M; i++) {
        cout << ans[i] << "\n";
    }
}