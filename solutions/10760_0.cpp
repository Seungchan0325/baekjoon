#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int N;

int main()
{
    cin >> N;
    vector<pair<int, int>> v(N);
    for(auto& [p, s] : v) cin >> s >> p;
    sort(v.begin(), v.end());

    vector<pair<int, int>> v1, v2;
    int idx = 0;
    for(auto [p, s] : v) {
        v1.emplace_back(p, p + s);
        v2.emplace_back(p - s, p);
        idx++;
    }
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    idx = 0;
    set<int> s;
    vector<pair<int, int>> lr;
    for(auto [a, b] : v1) {
        while(idx < N && v2[idx].first <= a) {
            s.insert(v2[idx].second);
            idx++;
        }
        auto it = s.upper_bound(b);
        if(it != s.begin()) {
            it--;
            lr.emplace_back(a, *it);
        }
    }

    int ans = 0;
    int lst = -100;
    for(auto [l, r] : lr) {
        if(lst < l) ans += r - l, lst = r;
        else ans += max(r - lst, 0), lst = max(lst, r);
    }
    cout << ans;
}