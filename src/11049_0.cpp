#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;
const int INF = INT_MAX;

int n, r[MAXN], c[MAXN], cache[MAXN][MAXN];

// r1 * c1 * c2
int dp(int left, int right) {
    if(left == right) return 0;
    int& ret = cache[left][right];
    if(ret != -1) return ret;
    
    ret = INF;
    for(int next = left; next < right; next++) {
        ret = min(dp(left, next) + dp(next+1, right) + r[left] * c[next] * c[right], ret);
    }

    return ret;
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) cin >> r[i] >> c[i];

    memset(cache, -1, sizeof(cache));
    int result = dp(0, n-1);
    cout << result;
}