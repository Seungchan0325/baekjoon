#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> g[55];

int dp(int u)
{
    vector<int> a;
    for(auto v : g[u]) {
        a.push_back(dp(v));
    }
    sort(a.begin(), a.end(), greater<>());
    int ans = 0;
    for(int i = 0; i < a.size(); i++) {
        ans = max(ans, a[i] + i + 1);
    }
    return ans;
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++) {
        int p; cin >> p;
        if(p != -1) g[p].push_back(i);
    }
    int ans = dp(0);
    cout << ans;
}