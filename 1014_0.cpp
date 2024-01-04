#include <bits/stdc++.h>

using namespace std;

const int MAXN = 11;

int n, m, room[MAXN], cache[MAXN][1<<MAXN];

int dp(int idx, int taken) {
    if(idx == m) return 0;
    int& ret = cache[idx][taken];
    if(ret != -1) return ret;

    ret = 0;
    for(int students = 0; students < (1<<n); students++) {
        if((room[idx] | students) != room[idx]) continue;
        if((taken & students) | ((taken<<1) & students) | ((taken>>1) & students)) continue;

        int cnt = __builtin_popcount(students);
        ret = max(cnt + dp(idx+1, students), ret);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    while(t--) {
        memset(room, 0, sizeof(room));
        memset(cache, -1, sizeof(cache));

        cin >> n >> m;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) {
                char c; cin >> c;
                if(c == '.')
                    room[j] |= (1<<i);
            }

        int result = dp(0, 0);
        cout << result << "\n";
    }
}