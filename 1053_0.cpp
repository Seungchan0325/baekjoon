#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

string s;
int cache[55][55];

int dp(int lo, int hi) {
    if(lo >= hi) return 0;

    int& ret = cache[lo][hi];
    if(ret != -1) return ret;

    if(s[lo] == s[hi]) return ret = dp(lo+1, hi-1);

    ret = INF;

    ret = min(dp(lo+1, hi) + 1, ret);
    ret = min(dp(lo, hi-1) + 1, ret);
    ret = min(dp(lo+1, hi-1) + 1, ret);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> s;
    int n = s.size();

    memset(cache, -1, sizeof(cache));
    int result = dp(0, n-1);

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            memset(cache, -1, sizeof(cache));
            swap(s[i], s[j]);
            result = min(dp(0, n-1) + 1, result);
            swap(s[i], s[j]);
        }
    }

    cout << result;
}