#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;
const int MAXS = 1050;

int N, S;
bool DP[MAXN][MAXS];

int main()
{
    cin >> N >> S;

    DP[2][0] = true;
    DP[3][1] = true;
    for(int i = 4; i <= N; i++) {
        for(int j = 1; j < i; j++) {
            for(int k = 1; k <= S; k++) {
                int prv = k - (j+1)*j/2;
                if(prv < 0) continue;
                DP[i][k] |= DP[i-j][prv];
            }
        }
    }

    cout << DP[N][S];
}