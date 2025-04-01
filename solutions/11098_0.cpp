#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<pair<int, string>> v(n);
        for(auto&[price, name]:v) cin >> price >> name;
        sort(v.begin(), v.end());
        cout << v[n-1].second << "\n";
    }
}