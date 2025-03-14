#include <bits/stdc++.h>

using namespace std;

#define int long long

int N, M;
vector<int> A[101010], B[101010];

int compute(vector<int> a, vector<int> b)
{
    int n = a.size();
    vector<int> dp(n);
    for(int i = 0; i < n; i++) {
        int cand = a[i];
        if(i >= 2 && b[i-1] + 1 == b[i]) cand += dp[i-2];
        else if(i >= 1 && b[i-1] + 1 != b[i]) cand += dp[i-1];
        dp[i] = cand;
        cand = 0;
        if(i > 0) cand = dp[i-1];
        dp[i] = max(dp[i], cand);
    }
    return dp[n-1];
}

signed main()
{
    cin >> N >> M;

    int ans = 0;

    for(int i = 1; i <= M; i++) {
        int l;
        cin >> l;
        for(int j = 1; j <= l; j++) {
            int p, v;
            cin >> p >> v;
            A[p].push_back(v);
            B[p].push_back(i);
        }
    }
    for(int i = 1; i <= N; i++) {
        if(A[i].size() > 0)
            ans += compute(A[i], B[i]);
    }
    cout << ans;
}