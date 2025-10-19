#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010101;
const int mod = 1e9 + 7;

int N, A[MAXN], dp[MAXN];
vector<int> v[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 1; i <= N; i++) {
        if(i+A[i] <= N) v[i+A[i]].push_back(i);
    }

    dp[0] = 1;
    for(int i = 1; i <= N; i++) {
        vector<int> prv;
        for(int j : v[i]) prv.push_back(j);
        if(i-A[i] >= 1) prv.push_back(i-A[i]);
        sort(prv.begin(), prv.end());
        prv.erase(unique(prv.begin(), prv.end()), prv.end());
        for(int j : prv) dp[i] = (dp[i] + dp[j-1]) % mod;
    }
    cout << dp[N] << "\n";
}