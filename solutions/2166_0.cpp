#include <bits/stdc++.h>

using namespace std;

using ll = long;

struct Point {
    ll x, y;
};

int main()
{
    int N;
    cin >> N;
    vector<Point> v(N);
    for(auto& [x, y] : v) cin >> x >> y;
    v.push_back(v[0]);
    ll s = 0;
    for(int i = 1; i < v.size(); i++) {
        s += v[i-1].x * v[i].y;
        s -= v[i-1].y * v[i].x;
    }
    if(s < 0) s = -s;
    cout << s/2 << ".";
    if(s%2) cout << "5";
    else cout << "0";
}