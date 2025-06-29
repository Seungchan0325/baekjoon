#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int n, a[5], mx[2][5], mn[2][5];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= 3; j++) {
            cin >> a[j];
        }
        int j = i&1;
        mx[j][1] = max(mx[j^1][1], mx[j^1][2]) + a[1];
        mx[j][2] = max({mx[j^1][1], mx[j^1][2], mx[j^1][3]}) + a[2];
        mx[j][3] = max(mx[j^1][3], mx[j^1][2]) + a[3];
        mn[j][1] = min(mn[j^1][1], mn[j^1][2]) + a[1];
        mn[j][2] = min({mn[j^1][1], mn[j^1][2], mn[j^1][3]}) + a[2];
        mn[j][3] = min(mn[j^1][3], mn[j^1][2]) + a[3];
    }

    cout << max({mx[n&1][1], mx[n&1][2], mx[n&1][3]}) << " " << min({mn[n&1][1], mn[n&1][2], mn[n&1][3]});
}