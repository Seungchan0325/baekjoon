#include <bits/stdc++.h>

using namespace std;

const int MAXN = 7070;

int lcs1[MAXN], lcs2[MAXN], prv[MAXN];
string a, b, ans;

void solve(int l, int r, int s, int e)
{
    if(r < l) return;
    if(l == r) {
        for(int i = s; i <= e; i++) {
            if(a[l-1] == b[i-1]) {
                ans.push_back(a[l-1]);
                return;
            }
        }
        return;
    }
    int m = (l + r) / 2;
    for(int i = s-1; i <= e+1; i++) {
        lcs1[i] = prv[i] = 0;
    }
    for(int i = l; i <= m; i++) {
        for(int j = s; j <= e; j++) {
            if(a[i-1] == b[j-1]) lcs1[j] = prv[j-1] + 1;
            else lcs1[j] = max(lcs1[j-1], prv[j]);
        }
        for(int j = s; j <= e; j++) prv[j] = lcs1[j];
    }
    for(int i = s-1; i <= e+1; i++) {
        lcs2[i] = prv[i] = 0;
    }
    for(int i = r; i >= m+1; i--) {
        for(int j = e; j >= s; j--) {
            if(a[i-1] == b[j-1]) lcs2[j] = prv[j+1] + 1;
            else lcs2[j] = max(lcs2[j+1], prv[j]);
        }
        for(int j = e; j >= s; j--) prv[j] = lcs2[j];
    }
    int mx = -1, opt = 0;
    for(int i = s-1; i <= e; i++) {
        if(lcs1[i] + lcs2[i+1] > mx) {
            mx = lcs1[i] + lcs2[i+1];
            opt = i;
        }
    }
    solve(l, m, s, opt);
    solve(m+1, r, opt+1, e);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> a >> b;
    solve(1, ssize(a), 1, ssize(b));
    cout << ans.size() << "\n";
    cout << ans << "\n";
}