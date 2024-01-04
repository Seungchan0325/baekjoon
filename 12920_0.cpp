#include <iostream>
#include <vector>

using namespace std;

int n, m, v, c, k, dn, dv[14*10001], dc[14*10001], dp[10001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>n>>m;

    for(int i=0; i<n; i++) {
        cin>>v>>c>>k;
        while(k != 0) {
            int part = k -(k>>1);
            dv[dn] = v * part;
            dc[dn] = c * part;
            dn++; k>>=1;
        }
    }

    for(int i=0; i<dn; i++) {
        for(int j=m; j>=dv[i]; j--) {
            dp[j] = max(dp[j], dp[j - dv[i]] + dc[i]);
        }
    }

    cout<<dp[m];
}