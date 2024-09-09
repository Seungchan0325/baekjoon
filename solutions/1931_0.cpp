#include <bits/stdc++.h>

using namespace std;

long long N;

signed main()
{
    cin >> N;
    vector<pair<long long, long long>> v(N);
    for(auto& [s, e] : v) cin >> s >> e;
    sort(v.begin(), v.end(), [](pair<long long, long long> a, pair<long long, long long> b) {
        if(a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });
    long long cnt = 0;
    long long l = 0;
    for(auto [s, e] : v) {
        if(l <= s) {
            cnt++;
            l = e;
        }
    }

    cout << cnt;
}