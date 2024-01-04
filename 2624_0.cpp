#include <bits/stdc++.h>

using namespace std;

int t, k, p[100], n[100], dp[10001];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>t>>k;
    for(int i=0; i<k; i++) cin>>p[i]>>n[i];

    dp[0] = 1;
    for(int i=0; i<k; i++) {
        for(int j=t; j>=0; j--) {
            for(int l=n[i]; l>=1; l--) {
                int price = p[i] * l;
                if(price <= j) {
                    dp[j] += dp[j-price];
                }
            }
        }
    }

    cout<<dp[t];
}