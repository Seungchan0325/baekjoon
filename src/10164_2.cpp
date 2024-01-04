#include <bits/stdc++.h>

using namespace std;

long long n, m, k, dp[20][20];

pair<int, int> covert_idx_to_x_y(int idx) {
    int a = 0;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            a++;
            if(a == idx) {
                return {j, i};
            }
        }
    }
}

int main() {
    cin>>n>>m>>k;

    auto [x, y] = covert_idx_to_x_y(k);
    if(k == 0) x = y = 1;

    dp[1][1] = 1;
    for(int i=1; i<=y; i++) {
        for(int j=1; j<=x; j++) {
            if(i == 1 && j == 1) continue;
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }

    for(int i=y; i<=n; i++) {
        for(int j=x; j<=m; j++) {
            if(i == 1 && j == 1) continue;
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }

    cout<<dp[n][m];
}