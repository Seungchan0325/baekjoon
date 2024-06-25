#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
const int INF = 1e8;

int N, A[MAXN], cache[MAXN][MAXN];

int dp(int l, int r)
{
    if(l >= r) return 0;

    int& ret = cache[l][r];
    if(ret != -1) return ret;

    ret = dp(l + 1, r);
    for(int i = l + 1; i <= r; i++) {
        ret = max(ret, dp(l+1, i-1) + dp(i+1, r) + (A[l] == A[i]));
    }

    return ret;
}

int main() {
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];

    memset(cache, -1, sizeof(cache));
    int result = dp(1, N);
    cout << result;
}