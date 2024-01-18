#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAX_LEN = 55;

ll dp[MAX_LEN][MAX_LEN];

ll skip;
bool flag = false;
void kth(int n, int open, string s) {
    if(skip < 0) return;

    if(n == 0) {
        if(skip == 0 && open != 0) {
            flag = true;
            cout << s;
        }
        if(open != 0) skip--;
        return;
    }

    ll bino = (1LL << n) - dp[n][open];
    if(0 < open && bino <= skip) {
        skip -= bino;
        return;
    }

    if(open < 0 && (1LL << n) <= skip) {
        skip -= (1LL << n);
        return;
    }

    if(open < 0) kth(n-1, open, s+"(");
    else kth(n-1, open+1, s+"(");
    kth(n-1, open-1, s+")");
}

int main() {
    ll n, k;
    cin >> n >> k;
    skip = k;

    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= i; j++) {
            ll l, r;
            l = r = 0;
            if(0 < j) l = dp[i-1][j-1];
            if(j < n) r = dp[i-1][j+1];
            dp[i][j] = l + r;
        }
    }

    kth(n, 0, "");
    if(!flag) cout << -1;
}