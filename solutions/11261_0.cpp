#include <bits/stdc++.h>

using namespace std;

int weight[55], preference[55], dp[5050];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        int w; cin >> w;
        for(int i = 1; i <= n; i++) cin >> weight[i];
        for(int i = 1; i <= n; i++) cin >> preference[i];
        for(int i = 0; i <= w; i++) dp[i] = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = w; j >= weight[i]; j--) {
                dp[j] = max(dp[j], dp[j-weight[i]]+preference[i]);
            }
        }
        cout << dp[w] << "\n";
    }
}