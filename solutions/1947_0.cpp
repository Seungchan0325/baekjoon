#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll M = 1000000000;
const int MAXN = 1000005;

int n;
ll dp1[MAXN], dp2[MAXN];

int main() {
    cin >> n;
    dp1[0] = dp1[1] = 0;
    dp1[2] = 1;
    dp2[2] = 1;
    for(int i = 3; i <= n; i++) {
        dp2[i] = (dp1[i-1] + dp1[i-2]) % M;
        dp1[i] = (dp2[i] * (i-1)) % M;
    }

    cout << dp1[n];
}