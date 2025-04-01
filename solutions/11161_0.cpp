#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t; cin >> t;
    while(t--) {
        int m; cin >> m;
        int ans = 0;
        int acc = 0;
        while(m--) {
            int p, q;
            cin >> p >> q;
            acc += p - q;
            ans = max(ans, -acc);
        }
        cout << ans << "\n";
    }
}