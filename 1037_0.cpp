#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int n;

int main() {
    cin >> n;

    int mn = INF, mx = -INF;
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        mn = min(mn, a);
        mx = max(mx, a);
    }

    cout << mn * mx;
}