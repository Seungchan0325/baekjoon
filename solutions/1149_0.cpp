#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int n, costs[MAXN][3], dp[MAXN][3];

int main() {
    cin>>n;
    for(int i = 0; i < n; i++)
        cin>>costs[i][0]>>costs[i][1]>>costs[i][2];
    
    memset(dp, 0x7F, sizeof(dp));
    dp[0][0] = costs[0][0];
    dp[0][1] = costs[0][1];
    dp[0][2] = costs[0][2];
    for(int i = 1; i < n; i++)
        for(int color = 0; color < 3; color++)
            for(int prev_color = 0; prev_color < 3; prev_color++) {
                if(color == prev_color) continue;
                dp[i][color] = min(dp[i-1][prev_color] + costs[i][color], dp[i][color]);
            }

    int ans = min({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
    cout<<ans;
}