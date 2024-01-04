#include <bits/stdc++.h>

using namespace std;

int n, m, board[1005][1005], dp[1005][1005];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n>>m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin>>board[i][j];

    dp[0][0] = board[0][0];
    for(int i=1; i<m; i++) dp[0][i] = dp[0][i-1] + board[0][i];

    for(int i=1; i<n; i++) {
        for(int j=0; j<m; j++) dp[i][j] = dp[i-1][j] + board[i][j];
        int sum = dp[i-1][0];
        for(int j=0; j<m; j++) {
            sum = max(sum, dp[i-1][j]) + board[i][j];
            dp[i][j] = max(dp[i][j], sum);
        }
        sum = dp[i-1][m-1];
        for(int j=m-1; j>=0; j--) {
            sum = max(sum, dp[i-1][j]) + board[i][j];
            dp[i][j] = max(dp[i][j], sum);
        }
    }

    cout<<dp[n-1][m-1];
}