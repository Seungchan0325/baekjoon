#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    map<string, int> r;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        r[s]++;
    }
    int k; cin >> k;
    int ans = 0;
    for(auto [s, c] : r) {
        int cnt = 0;
        for(auto c : s) cnt += c == '0';
        if(cnt <= k && (k-cnt)%2 == 0) ans = max(ans, c);
    }
    cout << ans;
}