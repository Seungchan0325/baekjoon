#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1005;
const int MAXK = 15;

int V, Q, K, R[MAXV], G[MAXV], B[MAXV], dp[MAXV][MAXK][3];
vector<int> graph[MAXV];

void dfs(int u, int p)
{
    dp[u][R[u]%K][0] += 1;
    dp[u][G[u]%K][1] += 1;
    dp[u][B[u]%K][2] += 1;
    for(auto v : graph[u]) {
        if(v == p) continue;
        dfs(v, u);
        int tmp[2*MAXK][3] = {0, };
        for(int i = 0; i < K; i++) {
            for(int j = 0; j < K; j++) {
                tmp[i+j][0] += ((dp[v][i][0] + dp[v][i][1]) * dp[u][j][0]) % Q;
                tmp[i+j][1] += ((dp[v][i][0] + dp[v][i][2]) * dp[u][j][1]) % Q;
                tmp[i+j][2] += (dp[v][i][1] * dp[u][j][2]) % Q;
                tmp[i+j][0] %= Q;
                tmp[i+j][1] %= Q;
                tmp[i+j][2] %= Q;
            }
        }

        for(int i = 0; i < K; i++) {
            dp[u][i][0] = dp[u][i][1] = dp[u][i][2] = 0;
        }

        for(int i = 0; i < 2*K; i++) {
            dp[u][i%K][0] = (dp[u][i%K][0] + tmp[i][0]) % Q;
            dp[u][i%K][1] = (dp[u][i%K][1] + tmp[i][1]) % Q;
            dp[u][i%K][2] = (dp[u][i%K][2] + tmp[i][2]) % Q;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> V >> Q >> K;
    for(int i = 1; i < V; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for(int i = 1; i <= V; i++) {
        cin >> R[i] >> G[i] >> B[i];
    }
    dfs(1, -1);
    int result = (dp[1][0][0] + dp[1][0][1] + dp[1][0][2]) % Q;
    cout << result;
}