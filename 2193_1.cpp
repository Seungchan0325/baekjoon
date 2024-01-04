#include <bits/stdc++.h>

using namespace std;

long long n, dp[2][91];

int main() {
    cin>>n;

    dp[1][1] = 1;
    dp[0][2] = 1;
    for(int i = 3; i <= n; i++) {
        dp[0][i] = dp[0][i-1] + dp[1][i-1];
        dp[1][i] = dp[0][i-1];
    }

    cout<<dp[0][n] + dp[1][n];
}