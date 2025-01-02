#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second
#define sz(A) ((int)(A.size()))

const int MAXN = 200005;

using lint = long long;

const lint INF = 1e18;

lint N, K, out[MAXN], in[3], mat[MAXN][3], ans, C[MAXN][3];

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) { cin >> C[i][0]; ans += C[i][0]; }
    for(int i = 1; i <= N; i++) { cin >> C[i][1]; ans += C[i][1]; }
    for(int i = 1; i <= N; i++) { cin >> C[i][2]; ans += C[i][2]; }


    priority_queue<pair<lint, int>, vector<pair<lint, int>>, greater<>> pq[3][3];
    for(int i = 1; i <= N; i++) {
        pq[0][0].emplace(C[i][0], i);
        pq[1][1].emplace(C[i][1], i);
        pq[2][2].emplace(C[i][2], i);
    }

    int iter = 0;

    while(true) {
        if(iter == 2 * N) break;

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(i == j)
                    while(pq[i][j].size() && out[pq[i][j].top().S] >= 2) pq[i][j].pop();
                else {
                    while(pq[i][j].size() && mat[pq[i][j].top().S][j]) pq[i][j].pop();
                    while(pq[i][j].size() && !mat[pq[i][j].top().S][i]) pq[i][j].pop();
                }
            }
        }

        lint mn = INF;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(i == j) {
                    if(pq[i][j].size() && in[i] < N-K)
                        mn = min(mn, pq[i][j].top().F);
                } else {
                    if(pq[i][i].size() && pq[i][j].size() && in[j] < N-K) {
                        mn = min(mn, pq[i][i].top().F + pq[i][j].top().F);
                    }

                    int k = 0 + 1 + 2 - i - j;
                    if(pq[i][i].size() && pq[i][j].size() && pq[j][k].size() && in[k] < N-K) {
                        mn = min(mn, pq[i][i].top().F + pq[i][j].top().F + pq[j][k].top().F);
                    }
                }
            }
        }

        ans -= mn;

        auto upd = [&](int i, int j)
        {
            for(int k = 0; k < 3; k++) {
                if(j == k) continue;
                pq[k][k].emplace(C[i][k], i);
                pq[j][k].emplace(-C[i][j] + C[i][k], i);
            }
        };

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(i == j) {
                    if(pq[i][j].size() && in[i] < N-K && pq[i][j].top().F == mn) {
                        int a = pq[i][j].top().S;
                        out[a]++;
                        mat[a][i]++;
                        in[i]++;
                        pq[i][j].pop();
                        upd(a, i);
                        goto ESCAPE;
                    }
                } else {
                    if(pq[i][i].size() && pq[i][j].size() && in[j] < N-K && pq[i][i].top().F + pq[i][j].top().F == mn) {
                        int a = pq[i][i].top().S;
                        int b = pq[i][j].top().S;
                        out[a]++;
                        mat[a][i]++;
                        mat[b][i]--;
                        mat[b][j]++;
                        in[j]++;
                        pq[i][i].pop();
                        pq[i][j].pop();
                        upd(a, i);
                        upd(b, j);
                        goto ESCAPE;
                    }

                    int k = 0 + 1 + 2 - i - j;
                    if(pq[i][i].size() && pq[i][j].size() && pq[j][k].size() && in[k] < N-K && pq[i][i].top().F + pq[i][j].top().F + pq[j][k].top().F == mn) {
                        int a = pq[i][i].top().S;
                        int b = pq[i][j].top().S;
                        int c = pq[j][k].top().S;
                        out[a]++;
                        mat[a][i]++;
                        mat[b][i]--;
                        mat[b][j]++;
                        mat[c][j]--;
                        mat[c][k]++;
                        in[k]++;
                        pq[i][i].pop();
                        pq[i][j].pop();
                        pq[j][k].pop();
                        upd(a, i);
                        upd(b, j);
                        upd(c, k);
                        goto ESCAPE;
                    }
                }
            }
        }

        ESCAPE:
        iter++;
    }

    cout << ans;
}