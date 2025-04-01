#include <bits/stdc++.h>

using namespace std;

set<pair<int, int>> vst;

int a, b;
vector<int> v;

void f(int l, int r)
{
    if(vst.count({l, r})) return;
    vst.insert({l, r});
    v.push_back(l);
    v.push_back(r);
    f(0, r);
    f(l, 0);
    f(a, r);
    f(l, b);
    int d = min(a - l, r);
    f(l + d, r - d);
    d = min(b - r, l);
    f(l - d, r + d);
}

int main()
{
    // for(a = 1; a <= 10; a++) {
    //     for(b = a; b <= 10; b++) {
    //         cout << "----------------\n";
    //         cout << a << " " << b << "\n";
    //         cout << "----------------\n";
    //         v.clear();
    //         vst.clear();
    //         f(0, 0);
    //         sort(v.begin(), v.end());
    //         v.erase(unique(v.begin(), v.end()), v.end());
    //         for(auto i : v) cout << i << "\n";
    //     }
    // }
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    while(t--) {
        int a, b, c;
        cin >> a >> b >> c;
        if(c % gcd(a, b) == 0) cout << "Yes\n";
        else cout << "No\n";
    }
}