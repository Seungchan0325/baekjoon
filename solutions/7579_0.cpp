#include <bits/stdc++.h>

using namespace std;

int n, m, sum, w[105], v[105], dp[10005];

int main() {
    cin>>n>>m;
    for(int i = 0; i < n; i++) cin>>w[i];
    for(int i = 0; i < n; i++) { cin>>v[i]; sum += v[i]; }

    for(int i = 0; i < n; i++)
        for(int j = sum; j >= v[i]; j--)
            dp[j] = max(dp[j - v[i]] + w[i], dp[j]);
    
    int result = lower_bound(dp, dp + sum, m) - dp;
    cout<<result;
}