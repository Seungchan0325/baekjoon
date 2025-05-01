#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXL = 33;
const int MAXN = 55;

int N, L;
string s[MAXN];
// ll cache[1<<MAXN][MAXN+1][MAXN+1][2];
ll cache[MAXL][MAXN][20][2];

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

ll dp(int l, int i, int j, int left)
{
    if(j == 0 && l == L) return 1;
    ll& ret = cache[l][i][j][left];
    if(ret != -1) return ret;
    ret = 0;
    if(j == 0) {
        // ret = 1;
        for(int k = 0; k < N; k++) {
            if(l + s[k].size() > L) continue;
            ret += dp(l + s[k].size(), k, s[k].size(), 0);
        }
        return ret;
    }
    int m = s[i].size();
    for(int k = 0; k < N; k++) {
        int m = s[k].size();
        if(l + s[k].size() > L) continue;
        if(checkin(s[i], s[k], j, left)) ret += dp(l + s[k].size(), i, j-m, left);
        if(checkextend(s[i], s[k], j, left)) ret += dp(l + s[k].size(), k, m-j, !left);
    }
    return ret;
}

int main()
{
    memset(cache, -1, sizeof(cache));
    cin >> N;
    cin >> L;
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
            if(possible) ans += dp(s[i].size(), i, n-c, l >= 0);
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
            if(possible) ans += dp(s[i].size(), i, n-c, l >= 0);
        }
    }

    cout << ans;
}