#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 987654321;
int n, dp[(int)1e6 + 5];

int main() {
    cin>>n;
    for(int i=2; i<=n; i++) {
        dp[i] = min({dp[i-1],
                    i % 2 == 0 ? dp[i / 2] : INF,
                    i % 3 == 0 ? dp[i / 3] : INF}) + 1;
    }
    cout<<dp[n]<<"\n";
}