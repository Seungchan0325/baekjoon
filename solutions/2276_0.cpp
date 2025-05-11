#include <bits/stdc++.h>

using namespace std;

const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};

int N, M;
int A[303][303], D[303][303];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> M >> N;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> A[i][j];
        }
    }
    memset(D, 0x7F, sizeof(D));
    priority_queue<tuple<int, int, int>> pq;
    D[0][0] = A[0][0];
    pq.emplace(-D[0][0], 0, 0);
    while(!pq.empty()) {
        auto [d, x, y] = pq.top(); pq.pop();
        d = -d;
        if(d > D[x][y]) continue;
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 0 || nx > N+1 || ny < 0 || ny > M+1) continue;
            if(max(D[x][y], A[nx][ny]) < D[nx][ny]) {
                D[nx][ny] = max(D[x][y], A[nx][ny]);
                pq.emplace(-D[nx][ny], nx, ny);
            }
        }
    }

    int ans = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            ans += D[i][j] - A[i][j];
        }
    }
    cout << ans;
}