#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int n, L, dp[MAXN];

int main()
{
    cin >> n >> L;
    vector<int> v(n);
    for(auto& i : v) cin >> i;
    sort(v.begin(), v.end());
    for(int i = 0; i < n; i++) {
        int j = upper_bound(v.begin(), v.end(), v[i]-L) - v.begin() - 1;
        dp[i] = lower_bound(v.begin(), v.end(), v[i]) - upper_bound(v.begin(), v.end(), v[i] - L);
        if(j >= 0) dp[i] += dp[j];
    }
    cout << dp[n-1] << "\n";
}