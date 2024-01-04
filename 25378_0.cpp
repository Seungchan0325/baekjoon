#include <iostream>

using namespace std;

const int NMAX = 2500;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, arr[NMAX+1], dp[NMAX+1]{0};
    cin>>n;
    for(int i=1; i<=n; i++) cin>>arr[i];

    for(int i=1; i<=n; i++) {
        dp[i] = dp[i-1] + 1;
        int remain = arr[i];
        for(int j=i-1; j>0; j--) {
            remain = arr[j] - remain;
            if(remain < 0) break;
            if(remain == 0) dp[i] = min(dp[j - 1] + i - j, dp[i]);
        }
    }

    cout<<dp[n];
}