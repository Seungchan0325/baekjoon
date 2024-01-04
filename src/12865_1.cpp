#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n, k, w, v;
    int dp[100001] {};

    scanf("%d %d", &n, &k);

    for(int i=0; i<n; i++) {
        scanf("%d %d", &w, &v);
        for(int j=k; j>=w; j--) {
            dp[j] = max(dp[j], dp[j-w]+v);
        }
    }

    printf("%d\n", dp[k]);
}