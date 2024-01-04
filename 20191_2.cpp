#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int n, m;
int cache[1'000'005];
string s, t;

int solve(int start) {
    if(start == n) return 0;
    int& ret = cache[start];
    if(ret != -1) return ret;

    int last = 0;
    while(t[last] != s[start] && last < m) last++;
    if(last == m) {
        cout << -1;
        exit(0);
    }

    ret = INF;
    for(int next = start + 1; next <= n && last < m; next++) {
        ret = min(solve(next), ret);
        last++;
        while(t[last] != s[next] && last < m) last++;
    }
    ret += 1;

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(cache, -1, sizeof(cache));
    cin >> s;
    cin >> t;
    n = s.size();
    m = t.size();

    int result = solve(0);
    cout << result;
}