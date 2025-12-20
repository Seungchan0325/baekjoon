#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

int N, M, A[MAXN], m[MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) cin >> A[i];
    m[0] = 1e9;
    for(int i = 1; i <= N; i++) m[i] = min(A[i], m[i-1]);
    int ans = -1e9;
    for(int i = 0; i <= M; i++) {
        ans = max(ans, A[N-i] - m[M-i+1]);
    }
    cout << ans << "\n";
}