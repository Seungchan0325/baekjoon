#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    pair<double, int> ans = max({make_pair(a/c + b/d, 0), make_pair(c/d + a/b, 1), make_pair(d/b + c/a, 2), make_pair(b/a + d/c, 3)});
    cout << ans.second;
}