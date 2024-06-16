#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;
const ll MAXN = 10000005;

ll DP[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    DP[0] = DP[1] = 1;
    DP[2] = DP[3] = 0;
    DP[4] = 2;
    for(int n = 5; n < MAXN; n++) {
        DP[n] = (n + 1) * DP[n - 1] - (n - 2) * DP[n - 2] - (n - 5) * DP[n - 3] + (n - 3) * DP[n - 4];
        DP[n] = (DP[n] % MOD + MOD) % MOD;
    }

    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        cout << DP[n] << "\n";
    }
}