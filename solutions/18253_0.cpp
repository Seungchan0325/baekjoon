#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int dr[] = {0, 0, 1, -1};
const int dc[] = {1, -1, 0, 0};

const int MAXN = 6;
const int MAXM = 101010;

ll N, M, Q, A[MAXN][MAXM], S[MAXM], E[MAXM], P[MAXM], DEP[MAXM], D[17][MAXN][MAXN][MAXM];

void dijkstra(int depth, int sr, int sc, int s, int e)
{
    priority_queue<tuple<ll, int, int>> pq;
    D[depth][sr][sr][sc] = A[sr][sc];
    pq.emplace(-A[sr][sc], sr, sc);
    while(!pq.empty()) {
        auto [d, r, c] = pq.top(); pq.pop();
        d = -d;
        if(D[depth][sr][r][c] < d) continue;
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nc < s || nc > e || nr < 1 || nr > N) continue;
            if(d + A[nr][nc] < D[depth][sr][nr][nc]) {
                D[depth][sr][nr][nc] = d + A[nr][nc];
                pq.emplace(-(d + A[nr][nc]), nr, nc);
            }
        }
    }
}

void DnC(int s, int e, int p, int depth)
{
    if(e < s) return;
    int m = (s + e) / 2;
    P[m] = p;
    S[m] = s;
    E[m] = e;
    DEP[m] = depth;
    for(int i = 1; i <= N; i++) {
        dijkstra(depth, i, m, s, e);
    }
    DnC(s, m-1, m, depth+1);
    DnC(m+1, e, m, depth+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> A[i][j];
        }
    }
    memset(D, 0x7F, sizeof(D));
    DnC(1, M, -1, 0);
    cin >> Q;
    while(Q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        int i = c1;
        ll ans = 1e18;
        while(i != -1) {
            assert(1 <= i && i <= M);
            if(S[i] <= c2 && c2 <= E[i]) {
                for(int j = 1; j <= N; j++) {
                    assert(0 <= DEP[i] && DEP[i] < 22);
                    ans = min(ans, D[DEP[i]][j][r1][c1] + D[DEP[i]][j][r2][c2] - A[j][i]);
                }
            }
            i = P[i];
        }
        cout << ans << "\n";
    }
}