#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for(auto&i:v) cin >> i;
    sort(v.begin(), v.end());
    int ans = 1e9;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int acc = 0;
            for(int k = 0; k < n; k++) {
                acc += min((v[i]-v[k])*(v[i]-v[k]), (v[j]-v[k])*(v[j]-v[k]));
            }
            ans = min(ans, acc);
        }
    }
    cout << ans;
}
