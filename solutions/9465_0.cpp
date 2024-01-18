#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n;
        int a[2][100001], dp[2][100001];
        scanf("%d", &n);

        for(int i=0; i<2; i++)
            for(int j=0; j<n; j++)
                scanf("%d", a[i]+j);
        
        dp[0][0] = dp[1][0] = 0;
        dp[0][1] = a[0][0]; dp[1][1] = a[1][0];
        for(int i=2; i<=n; i++) {
            dp[0][i] = max(dp[1][i-1], dp[1][i-2]) + a[0][i-1];
            dp[1][i] = max(dp[0][i-1], dp[0][i-2]) + a[1][i-1];
        }
        printf("%d\n", max(dp[0][n], dp[1][n]));
    }
}