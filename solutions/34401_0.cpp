#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main()
{
    int n, p, k;
    cin >> n >> p >> k;
    vector<pair<int, int>> v(n);
    for(auto& [t, a] : v) cin >> t >> a;
    sort(v.begin(), v.end());

    deque<pair<int, int>> dq[6];
    for(auto& [t, a] : v) dq[a].push_back(pair(t, a));

    int ans = 0;
    int cnt = 0;
    for(int i = 0; cnt < n; i++) {
        int r = k;
        while(r) {
            int mn = 1e9;
            int mni = 0;
            for(int j = 1; j <= r; j++) {
                if(dq[j].size() && dq[j].front().first < mn) {
                    mn = dq[j].front().first;
                    mni = j;
                }
            }

            if(mni == 0 || mn > p * i) break;

            r -= mni;
            ans += p*i - mn;
            cnt++;
            dq[mni].pop_front();
        }
    }
    cout << ans << "\n";
}