#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;
const int mod = 1e9 + 7;

struct Query {
    int l, r, idx;
};

int N, M, a[MAXN], Q, ans[MAXN], dp[MAXN][20];

void DnC(int l, int r, vector<Query> qs)
{
    if(r < l || qs.empty()) return;
    int m = (l + r) / 2;
    memset(dp[m], 0, sizeof(dp[m]));
    dp[m][0]++; dp[m][a[m]%M]++;
    for(int i = m-1; i >= l; i--) {
        memset(dp[i], 0, sizeof(dp[i]));
        for(int j = 0; j < M; j++) {
            dp[i][j] = (dp[i][j] + dp[i+1][j]) % mod;
            dp[i][(j+a[i])%M] = (dp[i][(j+a[i])%M] + dp[i+1][j]) % mod;
        }
    }

    memset(dp[m+1], 0, sizeof(dp[m+1]));
    dp[m+1][0]++; dp[m+1][a[m+1]%M]++;
    for(int i = m+2; i <= r; i++) {
        memset(dp[i], 0, sizeof(dp[i]));
        for(int j = 0; j < M; j++) {
            dp[i][j] = (dp[i][j] + dp[i-1][j]) % mod;
            dp[i][(j+a[i])%M] = (dp[i][(j+a[i])%M] + dp[i-1][j]) % mod;
        }
    }
    
    vector<Query> lef, rig;
    for(Query q : qs) {
        if(q.r < m) lef.push_back(q);
        else if(m+1 < q.l) rig.push_back(q);
        else {
            if(q.r == m) {
                ans[q.idx] = dp[q.l][0];
            } else if(q.l == m+1) {
                ans[q.idx] = dp[q.r][0];
            } else {
                int now[20] = {0};
                for(int i = 0; i < M; i++) {
                    for(int j = 0; j < M; j++) {
                        now[(i+j)%M] = (now[(i+j)%M] + (ll)dp[q.l][i] * dp[q.r][j] % mod) % mod;
                    }
                }
                ans[q.idx] = now[0];
            }
        }
    }
    DnC(l, m-1, lef);
    DnC(m+1, r, rig);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i <= N; i++) cin >> a[i];
    cin >> Q;
    vector<Query> q(Q);
    for(int i = 0; i < Q; i++) {
        q[i].idx = i;
        cin >> q[i].l >> q[i].r;
    }
    DnC(1, N, q);
    for(int i = 0; i < Q; i++) cout << ans[i] << "\n";
}