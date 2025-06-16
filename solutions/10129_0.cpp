#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010101;

int n, d[MAXN], dp[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; i++) cin >> d[i];
    int q;
    cin >> q;
    while(q--) {
        int k;
        cin >> k;
        deque<int> dq;
        dp[1] = 0;
        dq.push_back(1);
        for(int i = 2; i <= n; i++) {
            while(i - dq.front() > k) dq.pop_front();
            dp[i] = dp[dq[0]] + (d[dq[0]] <= d[i]);
            while(dq.size() && (dp[dq.back()] > dp[i] || (dp[dq.back()] == dp[i] && d[dq.back()] < d[i]))) dq.pop_back();
            dq.push_back(i);
        }
        cout << dp[n] << "\n";
    }
}