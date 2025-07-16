#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010101;

int n, dp[MAXN][3];
string a, b;

int main()
{
    cin >> n;
    cin >> a;
    cin >> b;
    a = '0' + a;
    b = '0' + b;
    dp[0][0] = dp[0][1] = 1e9;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 3; j++) {
            dp[i][j] = 1e9;
            for(int k = 0; k < 3; k++) {
                char p = (k==0 || k==2 && a[i-1]=='0' ? '0' : '1'); // i-1 == 0 이라면 항상 '0'
                char c = (j==0 || j==2 && a[i]=='0' ? '0' : '1');
                bool pxor = p != b[i-1];
                bool cxor = c != b[i];
                dp[i][j] = min(dp[i][j], dp[i-1][k] + (!pxor && cxor) + (j < 2 && j != k));
            }
        }
    }

    cout << min({dp[n][0], dp[n][1], dp[n][2]}) << "\n";
}