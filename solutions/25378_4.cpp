#include <iostream>

using namespace std;

int n, arr[2501], dp1[2501];
bool dp2[2501][2501];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>n;
    for(int i=1; i<=n; i++) cin>>arr[i];

    for(int i=1; i<=n; i++) {
        int remain = arr[i];
        for(int j=i+1; j<=n; j++) {
            remain = arr[j] - remain;
            if(remain < 0) break;
            if(remain == 0) dp2[i][j] = true;
        }
    }

    dp1[0] = 0;
    dp1[1] = 1;
    for(int i=2; i<=n; i++) {
        dp1[i] = dp1[i-1] + 1;
        for(int j=1; j<i; j++) {
            if(dp2[j][i]) {
                dp1[i] = min(dp1[i], dp1[j - 1] + i - j);
            }
        }
    }

    cout<<dp1[n];
}