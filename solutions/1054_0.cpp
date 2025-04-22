#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const int MAXN = 13;

int N;
string s[MAXN];
ll cache[1<<MAXN][MAXN+1][MAXN+1][2];

bool checkin(const string& a, const string& b, int i, int left)
{
    int n = a.size();
    int m = b.size();
    if(b.size() > i) return false;
    if(left) {
        auto s = a.substr(0, i);
        s = s.substr(s.size() - m);
        reverse(s.begin(), s.end());
        return s == b;
    } else {
        auto s = a.substr(n-i);
        s = s.substr(0, m);
        reverse(s.begin(), s.end());
        return s == b;
    }
}
bool checkextend(const string& a, const string& b, int i, int left)
{
    int n = a.size();
    int m = b.size();
    if(b.size() <= i) return false;
    if(left) {
        auto s = a.substr(0, i);
        auto ss = b.substr(0, i);
        reverse(s.begin(), s.end());
        return s == ss;
    } else {
        auto s = a.substr(n-i);
        auto ss = b.substr(m-i);
        reverse(s.begin(), s.end());
        return s == ss;
    }
}

ll dp(int taken, int i, int j, int left)
{
    ll& ret = cache[taken][i][j][left];
    if(ret != -1) return ret;
    ret = 0;
    if(j == 0) {
        ret = 1;
        for(int k = 0; k < N; k++) {
            if(taken&(1<<k)) continue;
            ret += dp(taken|(1<<k), k, s[k].size(), 0);
        }
        return ret;
    }
    int m = s[i].size();
    for(int k = 0; k < N; k++) {
        if(taken&(1<<k)) continue;
        int m = s[k].size();
        if(checkin(s[i], s[k], j, left)) ret += dp(taken|(1<<k), i, j-m, left);
        if(checkextend(s[i], s[k], j, left)) ret += dp(taken|(1<<k), k, m-j, !left);
    }
    return ret;
}

int main()
{
    memset(cache, -1, sizeof(cache));
    cin >> N;
    for(int i = 0; i < N; i++) cin >> s[i];

    ll ans = 0;

    for(int i = 0; i < N; i++) {
        int n = s[i].size();
        for(int j = 0; j < n; j++) {
            int c = -1;
            int l = j;
            int r = j;
            bool possible = true;
            while(l >= 0 && r < n) {
                if(s[i][l] != s[i][r]) {
                    possible = false;
                    break;
                }
                c += 2;
                l--; r++;
            }
            if(possible) ans += dp(1<<i, i, n-c, l >= 0);
        }
        for(int j = 0; j < n; j++) {
            int c = 0;
            int l = j-1;
            int r = j;
            bool possible = true;
            while(l >= 0 && r < n) {
                if(s[i][l] != s[i][r]) {
                    possible = false;
                    break;
                }
                c += 2;
                l--; r++;
            }
            if(possible) ans += dp(1<<i, i, n-c, l >= 0);
        }
    }

    cout << ans;
}