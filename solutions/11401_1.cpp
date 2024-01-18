#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD = 1000000007;

ll Pow(int a, int x)
{
    if(x == 0) return 1;
    if(x & 1) return ((ll)Pow(a, x - 1) * a) % MOD;
    ll p = Pow(a, x / 2);
    return (p * p) % MOD;
}

ll Bino(int n, int k)
{
    ll A = 1, B = 1;
    for(int i = n - k + 1; i <= n; i++) A = (A * i) % MOD;
    for(int i = 1; i <= k; i++) B = (B * i) % MOD;
    return ((A % MOD) * Pow(B, MOD - 2) % MOD) % MOD;
}

int main() {
    int n, k;
    cin >> n >> k;
    int result = Bino(n, k);
    cout << result;
}