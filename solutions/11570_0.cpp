#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
const int INF = 987654321;

int N, A[MAXN], cache[MAXN][MAXN];

int dp(int n, int lst)
{
    if(n == N) return 0;
    int& ret = cache[n][lst+1];
    if(ret != -1) return ret;

    ret = INF;
    ret = min(ret, dp(n + 1, lst) + (0 < n ? abs(A[n] - A[n-1]) : 0));
    ret = min(ret, dp(n + 1, n - 1) + (0 <= lst ? abs(A[n] - A[lst]) : 0));
    return ret;
}

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> A[i];
    }
    
    memset(cache, -1, sizeof(cache));
    int result = dp(0, -1);
    cout << result;
}