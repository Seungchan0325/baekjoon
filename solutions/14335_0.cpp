#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1001;
map<char, ll> c2i;
ll N, nxt[MAXN][62], cache[MAXN];

ll dp(int n)
{
    if(n == N) return 1;
    ll& ret = cache[n];
    if(ret != -1) return ret;

    ret = 1;
    for(ll i = 0; i < 62; i++) {
        ret = (ret + dp(nxt[n][i]));
    }
    return ret;
}

int main()
{
    ll idx = 0;
    for(char c = 'a'; c <= 'z'; c++) c2i[c] = idx++;
    for(char c = 'A'; c <= 'Z'; c++) c2i[c] = idx++;
    for(char c = '0'; c <= '9'; c++) c2i[c] = idx++;
    ll t;
    cin >> t;
    while(t--) {
        string s;
        cin >> s;
        N = s.size();
        s = "#" + s;
        
        for(int i = 0; i < 62; i++) nxt[N][i] = -1;
        for(int i = N-1; i >= 0; i--) {
            memcpy(nxt[i], nxt[i+1], sizeof(nxt[0]));
            nxt[i][c2i[s[i+1]]] = i+1;
        }

        memset(cache, -1, sizeof(cache));
        ll result = (dp(0));
        cout << result << "\n";
    }
}