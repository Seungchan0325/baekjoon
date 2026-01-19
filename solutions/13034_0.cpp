#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

int N, dp[MAXN];

int main()
{
    cin >> N;
    for(int i = 2; i <= N; i++) {
        set<int> s;
        for(int j = 1; j < i; j++) s.insert(dp[j-1]^dp[i-j-1]);
        while(s.contains(dp[i])) dp[i]++;
    }
    cout << (dp[N] ? 1 : 2) << "\n";
}