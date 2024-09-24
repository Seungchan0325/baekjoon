#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int di[4] = {0, 0, -1, 1};
const int dj[4] = {-1, 1, 0, 0};

int N, M;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    vector<string> B(N+2);
    for(int i = 1; i <= N; i++) {
        cin >> B[i];
        B[i] = " " + B[i] + " ";
    }

    priority_queue<tuple<int, int, int>> pq;
    vector<vector<int>> D(N+2, vector<int>(M+2, INF));
    for(int i = 1; i <= M; i++) {
        pq.emplace(0, N, i);
        D[N][i] = 0;
    }

    while(!pq.empty()) {
        auto [d, i, j] = pq.top(); pq.pop();
        d=-d;

        if(D[i][j] < d) continue;

        if(B[i][j] == '#') {
            for(int k = 0; k < 4; k++) {
                int ni = i + di[k];
                int nj = j + dj[k];
                if(1 <= ni && ni <= N && 1 <= nj && nj <= M && B[ni][nj] == '#' && d < D[ni][nj]) {
                    D[ni][nj] = d;
                    pq.emplace(-d, ni, nj);
                }
            }
        }

        if(i > 1) {
            if(B[i][j] == '#' && B[i-1][j] == '.' && d < D[i-1][j]) {
                D[i-1][j] = d;
                pq.emplace(-d, i-1, j);
            } else if(d+1 < D[i-1][j]) {
                D[i-1][j] = d + 1;
                pq.emplace(-d-1, i-1, j);
            }
        }
    }

    vector<string> A(N+2, string(M+2, '.'));
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(B[i][j] == '#')
                A[i+D[i][j]][j] = '#';
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cout << A[i][j];
        }
        cout << "\n";
    }
}