#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXR = 2020;
const ll inf = 1e18;

ll R, K, dp[MAXR][MAXR], s[MAXR][MAXR];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> R >> K;
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= K; j++) {
            cin >> s[i][j];
        }
    }

    for(int i = R; i >= 1; i--) {
        ll mn1 = inf, mn2 = inf, mx1 = -inf, mx2 = -inf;
        int mni = -1, mxi = -1;
        for(int j = 1; j <= K; j++) {
            ll k = dp[i+1][j];
            if(i%2) k += s[i][j];
            else k -= s[i][j];
            if(k > mx1) {
                mx2 = mx1;
                mxi = j;
                mx1 = k;
            } else if(k > mx2) {
                mx2 = k;
            }
            if(k < mn1) {
                mn2 = mn1;
                mni = j;
                mn1 = k;
            } else if(k < mn2) {
                mn2 = k;
            }
        }
        for(int j = 1; j <= K; j++) {
            if(i%2) {
                if(mxi == j) dp[i][j] = max(mx2, dp[i+1][j]);
                else dp[i][j] = max(mx1, dp[i+1][j]);
            } else {
                if(mni == j) dp[i][j] = min(mn2, dp[i+1][j]);
                else dp[i][j] = min(mn1, dp[i+1][j]);
            }
        }
    }
    ll mn = -inf;
    for(int i = 1; i <= K; i++) {
        mn = max(mn, dp[2][i] + s[1][i]);
    }

    if(mn <= 0) cout << "ibasic ";
    else cout << "djangg7 ";
    cout << abs(mn) << "\n";
}
