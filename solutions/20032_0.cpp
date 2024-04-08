#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<tuple<int, int, int>> v(n);
    int i = 0;
    for(auto& [x, y, idx] : v) {
        cin >> x >> y;
        idx = ++i;
    }

    sort(v.begin(), v.end());
    cout << 2*n-1 << "\n";
    for(auto [x, y, idx] : v) cout << idx << " ";
    v.pop_back();
    reverse(v.begin(), v.end());
    for(auto [x, y, idx] : v) cout << idx << " ";
    cout << "\n";
}