#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for(auto&i:v) cin >> i.first;
    for(auto&i:v) cin >> i.second;
    sort(v.begin(), v.end());

    vector<int> dp(n);
    int mx = 0;
    for(int i = 0; i < n; i++) {
        dp[i] = min(v[i].first, v[i].second);
        for(int j = 0; j < i; j++) {
             if(v[j].second < v[i].second)
                dp[i] = max(dp[i], dp[j] + min(v[i].first, v[i].second));
        }
        mx = max(mx, dp[i]);
    }
    for(int i = 0; i < n; i++) mx += max(v[i].first, v[i].second);
    cout << mx;
}