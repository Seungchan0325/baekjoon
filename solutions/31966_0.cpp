#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MOD = 1e9 + 7;

using ll = long long;

ll N, DP[MAXN][4];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;

    DP[0][3] = 1;
    for(int i = 1; i <= N; i++) {
        int A, B;
        cin >> A >> B;

        DP[i][0] = (DP[A][0] + DP[B][3] + DP[B][0]) % MOD;
        DP[i][1] = (DP[B][1] + DP[A][3] + DP[A][1]) % MOD;
        DP[i][2] = (DP[A][1] * DP[B][3] + DP[B][0] * DP[A][3] + DP[A][2] + DP[B][2]) % MOD;
        DP[i][3] = (DP[A][3] + DP[B][3]) % MOD;

        cout << (DP[i][0] + DP[i][1] + DP[i][2] + 1) % MOD << "\n";
    }
}