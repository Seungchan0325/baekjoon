#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2020;

int N;
int dp[MAXN][MAXN], p1, p3, p5, pp;
string A, B;

signed main()
{
    cin >> N;
    cin >> A; A = " " + A;
    cin >> B; B = " " + B;
    cin >> p1 >> p3 >> p5 >> pp;

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for(int i = 0; i <= N; i++) {
        for(int j = 0; j <= N; j++) {
            if(i >= 1 && A[i] == '0') dp[i][j] = min(dp[i][j], dp[i-1][j]);
            if(j >= 1 && B[j] == '0') dp[i][j] = min(dp[i][j], dp[i][j-1]);
            for(int k = 1; k <= 1; k++) {
                if(i >= k) dp[i][j] = min(dp[i][j], dp[i-k][j] + p1);
            }
            for(int k = 1; k <= 3; k++) {
                if(i >= k) dp[i][j] = min(dp[i][j], dp[i-k][j] + p3);
            }
            for(int k = 1; k <= 5; k++) {
                if(i >= k) dp[i][j] = min(dp[i][j], dp[i-k][j] + p5);
            }
            
            for(int k = 1; k <= 1; k++) {
                if(i >= k) dp[i][j] = min(dp[i][j], dp[i][j-k] + p1);
            }
            for(int k = 1; k <= 3; k++) {
                if(i >= k) dp[i][j] = min(dp[i][j], dp[i][j-k] + p3);
            }
            for(int k = 1; k <= 5; k++) {
                if(i >= k) dp[i][j] = min(dp[i][j], dp[i][j-k] + p5);
            }
            if(i == j) {
                for(int k = 1; k <= 4; k++) {
                    if(i >= k) dp[i][j] = min(dp[i][j], dp[i-k][j-k] + pp);
                }
            }
        }
    }
    cout << dp[N][N];
}