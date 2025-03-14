#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main()
{
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for(int i = 0; i < N; i++) cin >> A[i];
    int ans = 0;
    int i = 0;
    int j = N-1;
    while(i < j) {
        int diff = abs(A[i] - A[j]);
        int cand = min(diff / K + diff % K, diff / K + 1 + K - (diff % K));
        ans += cand;
        i++;
        j--;
    }
    cout << ans;
}