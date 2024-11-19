#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 505;

const int di[] = {0, 0, -1, 1};
const int dj[] = {-1, 1, 0, 0};

bool vst[MAXN][MAXN];
ll N, M, K, X, A[MAXN][MAXN];

bool chk(ll t)
{
    queue<pair<int, int>> q;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            vst[i][j] = false;
            for(int k = 0; k < 4; k++) {
                int ni = i + di[k];
                int nj = j + dj[k];
                if(ni < 1 || ni > N || nj < 1 || nj > M) continue;

                if(A[ni][nj] - A[i][j] > t) {
                    vst[i][j] = true;
                    q.emplace(i, j);
                    break;
                }
            }
        }
    }

    int cnt = 0;
    while(!q.empty()) {
        cnt++;
        auto [i, j] = q.front(); q.pop();
        for(int k = 0; k < 4; k++) {
            int ni = i + di[k];
            int nj = j + dj[k];
            if(ni < 1 || ni > N || nj < 1 || nj > M || vst[ni][nj]) continue;
            
            if(X - A[ni][nj] > t) {
                vst[ni][nj] = true;
                q.emplace(ni, nj);
            }
        }
    }

    return cnt <= K;
}

int main()
{
    cin >> N >> M >> K >> X;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> A[i][j];
        }
    }

    ll lo = -1;
    ll hi = 1e18;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(chk(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi;
}