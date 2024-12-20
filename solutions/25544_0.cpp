#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

vector<pii> lis(vector<array<int, 3>> v)
{
    vector<int> l;
    vector<pair<int, int>> len;
    for(auto i : v) {
        if(l.empty() || l.back() < i[1]) l.push_back(i[1]);
        else {
            *lower_bound(l.begin(), l.end(), i[1]) = i[1];
        }
        len.emplace_back(i[2], upper_bound(l.begin(), l.end(), i[1]) - l.begin());
    }
    sort(len.begin(), len.end());
    return len;
}

int main()
{
    int n;
    cin >> n;
    vector<array<int, 3>> v(n);
    for(auto& [x, y, idx] : v) cin >> x >> y;
    for(int i = 1; i < n; i++) v[i][2] = v[i-1][2] + 1;

    sort(v.begin(), v.end(), [](array<int, 3> a, array<int, 3> b) {
        if(a[0] != b[0]) return a[0] < b[0];
        return a[1] > b[1];
    });
    auto l1 = lis(v);

    for(auto& [x, y, idx] : v) y = -y;
    sort(v.begin(), v.end(), [](array<int, 3> a, array<int, 3> b) {
        if(a[0] != b[0]) return a[0] < b[0];
        return a[1] > b[1];
    });
    auto l2 = lis(v);

    sort(v.begin(), v.end(), [](array<int, 3> a, array<int, 3> b) {
        if(a[0] != b[0]) return a[0] > b[0];
        return a[1] > b[1];
    });
    auto l3 = lis(v);

    for(auto& [x, y, idx] : v) y = -y;
    sort(v.begin(), v.end(), [](array<int, 3> a, array<int, 3> b) {
        if(a[0] != b[0]) return a[0] > b[0];
        return a[1] > b[1];
    });
    auto l4 = lis(v);

    int ans = -1;
    for(int i = 0; i < n; i++) {
        if(l1[i].second > 1 && l2[i].second > 1 && l3[i].second > 1 && l4[i].second > 1) {
            ans = max(ans, l1[i].second + l2[i].second + l3[i].second + l4[i].second - 4 + 1);
        }
    }

    if(ans == -1) cout << "-1";
    else cout << n - ans;
}