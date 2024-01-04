#include <bits/stdc++.h>

using namespace std;

const int MAXN = 17;

int n, graph[MAXN][MAXN], cache[MAXN][11][1<<MAXN];

int dp(int cur, int lowest, int taken) {
    int& ret = cache[cur][lowest][taken];
    if(ret != -1) return ret;

    ret = 0;
    for(int i = 0; i < n; ++i) {
        if(taken & (1 << i)) continue;

        if(lowest <= graph[cur][i]) {
            ret = max(dp(i, graph[cur][i], taken | (1 << i)) + 1, ret);
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            char c; cin >> c;
            graph[i][j] = c - '0';
        }

    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0, 1) + 1;
    cout << result << "\n";
}