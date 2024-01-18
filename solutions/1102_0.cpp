#include <bits/stdc++.h>

using namespace std;

const int MAXN = 17;
const int INF = 987654321;

int n, p;
int costs[MAXN][MAXN];
int cache[1<<MAXN];

int solve(int cnt, int taken) {
    if(cnt >= p) return 0;

    int& ret = cache[taken];
    if(ret != -1) return ret;

    ret = INF;
    for(int i = 0; i < n; i++) {
        if(taken & (1<<i)) continue;
        for(int j = 0; j < n; j++) {
            if(!(taken & (1<<j))) continue;

            ret = min(solve(cnt+1, taken | (1<<i)) + costs[j][i], ret);
        }
    }

    return ret;
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> costs[i][j];
    int cnt = 0;
    int taken = 0;
    for(int i = 0; i < n; i++) {
        char c; cin >> c;
        if(c == 'Y') {
            cnt++;
            taken |= 1 << i;
        }
    }
    cin >> p;

    if(cnt == 0) {
        if(p == 0) cout << 0;
        else cout << -1;
        return 0;
    }

    memset(cache, -1, sizeof(cache));
    int result = solve(cnt, taken);
    cout << result;
}