#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

ll N, A[MAXN], B[MAXN], DP[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i] >> B[i];
    sort(A+1, A+N+1);
    sort(B+1, B+N+1);
    for(int i = 1; i <= N; i++) {
        DP[i] = 1e18;

        if(A[i] != B[i]) DP[i] = DP[i-1] + abs(A[i] - B[i]);
        if(i <= 2) {
            DP[i] = min({
                DP[i],
                DP[i-2] + abs(A[i-1] - B[i]) + abs(B[i-1] - A[i]),
            });
        } else {
            DP[i] = min({
                DP[i],
                DP[i-2] + abs(A[i-1] - B[i]) + abs(B[i-1] - A[i]),
                DP[i-3] + abs(A[i-2] - B[i-1]) + abs(A[i-1] - B[i]) + abs(A[i] - B[i-2]),
                DP[i-3] + abs(A[i-2] - B[i]) + abs(A[i-1] - B[i-2]) + abs(A[i] - B[i-1]),
            });
        }
    }
    cout << DP[N];
}