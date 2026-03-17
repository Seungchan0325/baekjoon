#include <bits/stdc++.h>

using namespace std;

int N, K, A[505], cache[505][505];

int dp(int i, int k)
{
    if(k < 0) return -1e9;
    if(i == 1) return 1;
    int& ret = cache[i][k];
    if(ret != -1) return ret;
    for(int j = 1; j < i; j++) {
        if(A[j] > A[i]) ret = max(ret, dp(j, k-1)+1);
        else ret = max(ret, dp(j, k)+1);
    }
    return ret;
}

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) cin >> A[i];
    memset(cache, -1, sizeof(cache));
    int ans = 0;
    for(int i = 1; i <= N; i++) ans = max(ans, dp(i, K));
    cout << ans << "\n";
}