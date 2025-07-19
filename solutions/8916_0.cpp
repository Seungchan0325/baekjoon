#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll mod = 9999991;

ll bino[22][22];

ll solve(vector<int> v)
{
    if(v.empty()) return 1;
    vector<int> a, b;
    for(int i = 1; i < v.size(); i++) {
        if(v[i] < v[0]) a.push_back(v[i]);
        else b.push_back(v[i]);
    }
    ll ans = bino[ssize(v)-1][a.size()];
    ans = ans * solve(a) % mod;
    ans = ans * solve(b) % mod;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    for(int i = 0; i <= 20; i++) {
        bino[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            bino[i][j] = (bino[i-1][j] + bino[i-1][j-1]) % mod;
        }
    }
    while(t--) {
        int n; cin >> n;
        vector<int> v(n);
        for(auto& i : v) cin >> i;
        auto ans = solve(v);
        cout << ans << "\n";
    }
}