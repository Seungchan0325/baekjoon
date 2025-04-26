#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, s;
    cin >> n >> s;
    if(s < n-2) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    vector<pair<int, int>> up, dw;
    bool hasarea = false;
    if(n&1) dw.emplace_back(0, 0);
    for(int i = 1; i <= n/2; i++) {
        if(i == n/2) {
            if(!hasarea) {
                up.emplace_back(i, s+1-(i&1));
                dw.emplace_back(i, 1-(i&1));
            } else {
                up.emplace_back(i, s-(i&1));
                dw.emplace_back(i, 1-(i&1));
            }
        } else {
            up.emplace_back(i, 2-(i&1));
            dw.emplace_back(i, 1-(i&1));
            if(hasarea) s-= 2;
            if(dw.size()) hasarea = true;
        }
        if(i == 1 && (n&1)) s-=1;
    }
    for(auto [x, y] : dw) cout << x << " " << y << "\n";
    reverse(up.begin(), up.end());
    for(auto [x, y] : up) cout << x << " " << y << "\n";
}