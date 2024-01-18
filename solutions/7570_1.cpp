#include <bits/stdc++.h>

using namespace std;

int n, kids[1000005], dp[1000005];

int main() {
    cin>>n;
    for(int i=0; i<n; i++) cin>>kids[i];

    int max_v = -1;
    for(int i=0; i<n; i++) {
        dp[kids[i]] = dp[kids[i] - 1] + 1;
        max_v = max(dp[kids[i]], max_v);
    }

    cout<<n-max_v;
}