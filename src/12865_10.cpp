#include <iostream>

using namespace std;

int n, k, w[101], v[101], dp[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>n>>k;
    for(int i=0; i<n; i++) {
        cin>>w[i]>>v[i];
    }

    for(int i=0; i<n; i++) {
        for(int j=k; j>=w[i]; j--) {
            dp[j] = max(dp[j], dp[j-w[i]]+v[i]);
        }
    }

    cout<<dp[k];
}