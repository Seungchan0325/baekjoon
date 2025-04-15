#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, p;
    cin >> n >> p;
    vector<pair<int, int>> l(p);
    for(auto& [s, e] : l) {
        cin >> s >> e;
        s--; e--;
        if(s > e) swap(s, e);
    }
    int ans = 1e9;
    for(int i = 0; i < n; i++) {
        vector<pair<int, int>> lines;
        for(auto [s, e] : l) {
            if(s <= i && i <= e) {
                lines.emplace_back(e, s + n);
            } else {
                if(e <= i) lines.emplace_back(s + n, e + n);
                else lines.emplace_back(s, e);
            }
        }
        sort(lines.begin(), lines.end());
        int mn, mx, c;
        mn = mx = -1;
        c = 0;
        for(auto [s, e] : lines) {
            if(mx < s) {
                c += mx - mn;
                mn = s;
                mx = e;
            } else {
                mx = max(mx, e);
            }
        }
        c += mx - mn;
        ans = min(ans, c);
    }
    cout << ans;
}