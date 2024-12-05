#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int SQRTN = 500;
const int MAXN = 200000;

int DP[MAXN][SQRTN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    DP[0][0] = 1;
    for(int i = 1; i < MAXN; i++) {
        for(int j = 1; j < min(SQRTN, i+1); j++) {
            DP[i][j] = (DP[i-1][j-1] + DP[i-j][j]) % MOD;
        }
    }
    for(int i = 0; i < MAXN; i++) {
        for(int j = 1; j < SQRTN; j++) {
            DP[i][j] = (DP[i][j] + DP[i][j-1]) % MOD;
        }
    }
    int t;
    cin >> t;
    while(t--) {
        int N;
        cin >> N;

        int ans = 0;
        for(int i = N%2; i * i <= N; i += 2) {
            ans = (ans + DP[(N-i*i)/2][i]) % MOD;
        }

        cout << ans << "\n";
    }
}