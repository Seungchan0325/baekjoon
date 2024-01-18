#include <bits/stdc++.h>

using namespace std;

const int MAXX = 10005;

int x, a, b, c, d;
int units[] = {1, 5, 10, 25};
int limit[4];
int dp[MAXX][5];

int main() {
    cin >> x;
    for(int i = 0; i < 4; i++) cin >> limit[i];

    memset(dp, -1, sizeof(dp));
    dp[0][0] = dp[0][1] = dp[0][2] = dp[0][3] = dp[0][4] = 0;

    for(int i = 1; i <= x; i++) {
        for(int unit = 0; unit < 4; unit++) {
            if(i - units[unit] < 0) break;
            if(dp[i-units[unit]][4] < 0) continue;
            if(dp[i][4] < dp[i-units[unit]][4] + 1 && dp[i-units[unit]][unit] < limit[unit]) {
                for(int j = 0; j < 5; j++) dp[i][j] = dp[i-units[unit]][j];
                dp[i][unit]++;
                dp[i][4]++;
            }
        }
    }

    if(dp[x][4] > 0)
        for(int i = 0; i < 4; i++) cout << dp[x][i] << " ";
    else
        cout << "0 0 0 0 ";
}