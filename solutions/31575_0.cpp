#include <bits/stdc++.h>

using namespace std;

int N, M, A[404][404], DP[404][404];

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> A[i][j];
        }
    }
    DP[1][1] = 1;
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            if(A[i][j] && (DP[ i-1][j] || DP[i][j-1])) DP[i][j] = 1;
        }
    }
    if(DP[M][N]) cout << "Yes\n";
    else cout << "No\n";
}