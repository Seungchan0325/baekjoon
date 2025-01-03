#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 2005;
const int MOD = 1e9 + 7;

ll N, cs, cf, DP[MAXN][MAXN];

int main()
{
    cin >> N >> cs >> cf;
    int sf = 0;
    DP[0][0] = 1;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            if(i == cs || i == cf) DP[i][j] = (DP[i-1][j] + DP[i-1][j-1]) % MOD;
            else DP[i][j] = (DP[i-1][j+1] * j + DP[i-1][j-1] * (j - sf)) % MOD;
        }
        if(i == cs || i == cf) sf++;
    }
    cout << DP[N][1];
}