#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e15;
const int MAXN = 305;

const int di[] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dj[] = {1, -1, 0, 0, 1, -1, 1, -1};

int N, M;
ll C[MAXN][MAXN], D[MAXN][MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> C[i][j];
            if(C[i][j] == -2) C[i][j] = 0;
            else if(C[i][j] == -1) C[i][j] = INF;
        }
    }
    C[0][0] = INF;
    C[1][0] = INF;
    C[0][1] = INF;
    C[N+1][M+1] = INF;
    C[N][M+1] = INF;
    C[N+1][M] = INF;

    for(int i = 0; i <= N+1; i++) {
        for(int j = 0; j <= M+1; j++) {
            D[i][j] = INF;
        }
    }

    priority_queue<tuple<ll, int, int>> pq;
    pq.emplace(0, N+1, 0);
    D[N+1][0] = 0;

    while(!pq.empty()) {
        auto [d, i, j] = pq.top(); pq.pop();
        d = -d;

        if(D[i][j] < d) continue;

        for(int k = 0; k < 8; k++) {
            int ni = i + di[k];
            int nj = j + dj[k];

            if(ni < 0 || ni > N+1 || nj < 0 || nj > M+1) continue;

            if(d + C[ni][nj] < D[ni][nj]) {
                D[ni][nj] = d + C[ni][nj];
                pq.emplace(-D[ni][nj], ni, nj);
            }
        }
    }

    if(D[0][M+1] >= INF) cout << "-1";
    else cout << D[0][M+1];
}