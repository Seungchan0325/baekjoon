#include <bits/stdc++.h>

using namespace std;

#define int long long

int n, k;

int compute(const vector<int>& a, const vector<int>& b)
{
    int i, j;
    i = j = 0;
    int s = 0;
    int mn = 0;
    int mx = 0;
    vector<int> v;
    while(i < a.size() || j < b.size()) {
        if((j >= b.size()) || (i < a.size() && a[i] < b[j])) {
            i++;
            s -= 1;
            mn = min(mn, s);
            mx = max(mx, s - mn);
        } else {
            j++;
            s += 1;
            mn = min(mn, s);
            mx = max(mx, s - mn);
        }
    }
    return mx + a.size();
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> k;
    vector<int> v(n);
    for(auto&i:v)cin>>i;
    auto vv = v;
    sort(vv.begin(), vv.end());
    vv.erase(unique(vv.begin(), vv.end()), vv.end());
    vector<vector<int>> vvv(vv.size());
    for(int i = 0; i < n; i++) {
        int idx = lower_bound(vv.begin(), vv.end(), v[i]) - vv.begin();
        vvv[idx].push_back(i);
    }
    int ans = 0;
    for(int i = 0; i < vv.size(); i++) {
        int idx = lower_bound(vv.begin(), vv.end(), vv[i] - k) - vv.begin();
        if(k != 0 && idx < n && vv[idx] == vv[i] - k) ans = max(ans, compute(vvv[i], vvv[idx]));
        else ans = max(ans, (int)vvv[i].size());
    }
    cout << ans;
}