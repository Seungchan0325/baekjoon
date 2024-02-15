#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXW = 605;
const int MAXL = 305;

char s[MAXL], ww[MAXW][30];
int w, l, n[MAXW], dp[MAXL];
vector<pair<int, int>> ranges_[MAXL];

int main()
{
    scanf("%d %d", &w, &l);
    scanf("%s", s + 1);
    for(int i = 1; i <= w; i++) {
        scanf("%s", ww[i] + 1);
        n[i] = strlen(&ww[i][1]);
    }

    for(int i = 1; i <= w; i++) {
        for(int j = 1; j <= l; j++) {
            if(s[j] != ww[i][n[i]]) continue;
            int cnt = 0;
            for(int k = j; k >= 1; k--) {
                if(s[k] == ww[i][n[i]-cnt]) {
                    if(++cnt == n[i]) {
                        ranges_[j].emplace_back(k, j - k + 1 - n[i]);
                        break;
                    }
                }
            }
        }
    }

    for(int i = 1; i <= l; i++) {
        dp[i] = dp[i-1] + 1;
        for(auto [j, erased] : ranges_[i]) {
            dp[i] = min(dp[j-1] + erased, dp[i]);
        }
    }
    cout << dp[l];
}