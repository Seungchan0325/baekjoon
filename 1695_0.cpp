#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int n, arr[5005];
int cache[5005][5005];

int dp(int lo, int hi) {
    if(lo >= hi) return 0;

    int& ret = cache[lo][hi];
    if(ret != -1) return ret;

    if(arr[lo] == arr[hi]) return ret = dp(lo+1, hi-1);

    ret = INF;

    ret = min(dp(lo+1, hi) + 1, ret);
    ret = min(dp(lo, hi-1) + 1, ret);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) cin >> arr[i];

    memset(cache, -1, sizeof(cache));
    int result = dp(0, n-1);

    cout << result;
}