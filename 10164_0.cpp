#include <bits/stdc++.h>

using namespace std;

long long n, m, k, dp[20][20];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n>>m>>k;

    int step = 1, x = 1, y = 1;
    dp[0][1] = 1;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(step++ == k) x = j, y = i;
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }

    cout<<dp[y][x] * dp[n-y+1][m-x+1];
}