#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> v;
vector<int> dp;

int main() {
    cin >> n;
    v.resize(n);
    dp.resize(n, -1);
    for(auto& i : v)
        cin >> i;

    dp[0] = v[0];
    dp[1] = v[0] + v[1];
    dp[2] = max(v[0], v[1]) + v[2];

    for(int i = 3; i < n; i++) {
        dp[i] = v[i]+max(dp[i-2], dp[i-3] + v[i-1]);
    }

    cout << dp[n-1];
}