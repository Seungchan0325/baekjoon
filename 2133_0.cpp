#include <iostream>

using namespace std;

int n;
int dp[31] = {1, 0, 3};

int main() {
    cin>>n;
    if(n&1) {
        cout<<0<<endl;
        return 0;
    }
    for (int i = 4; i <= n; i = i + 2) {
        dp[i] = dp[i - 2] * dp[2];
        for (int j = i - 4; j >= 0; j = j - 2)
            dp[i] = dp[i] + (dp[j] * 2);
    }
    cout<<dp[n]<<endl;
}