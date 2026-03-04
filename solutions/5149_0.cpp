#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;
const int inf = 1e9;

int n, m, x[MAXN], y[MAXN];

int main()
{
    int tc; cin >> tc;
    for(int ts = 1; ts <= tc; ts++) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++) cin >> x[i] >> y[i];

        int l = inf;
        int r = -inf;
        int b = inf;
        int t = -inf;
        for(int i = 0; i < m; i++) {
            int j;
            cin >> j;
            l = min(l, x[j]);
            r = max(r, x[j]);
            b = min(b, y[j]);
            t = max(t, y[j]);
        }

        int cnt = 0;
        for(int i = 1; i <= n; i++) {
            if(l <= x[i] && x[i] <= r && b <= y[i] && y[i] <= t) cnt++;
        }
        cout << "Data Set " << ts << ":\n";
        cout << cnt << "\n\n";
    }
}