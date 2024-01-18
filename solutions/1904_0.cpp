#include <iostream>

using namespace std;

const int MOD = 15746;
int n;
long long dp[1000000] = {0, 1, 2};

int main() {
    cin>>n;

    for(int i=3; i<=n; i++) {
        dp[i] = (dp[i-1] + dp[i-2]) % MOD;
    }

    cout<<dp[n]<<endl;
}