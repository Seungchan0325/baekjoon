#include <bits/stdc++.h>

using namespace std;

using ll = __int128_t;

const ll MAXN = 1000005;
const ll MOD = 1e9 + 7;

ll pow(ll x, ll n)
{
    if(n < 0) return 0; 
    if(n == 0) return 1;
    if(n&1) return pow(x, n-1)*x % MOD;
    ll half = pow(x, n/2);
    return half*half % MOD;
}

int main()
{
    long long n, m;
    cin >> n >> m;

    ll N = n;
    ll M = m;

    if(M == 1) {
        cout << (long long)((pow((ll)2, N)-1 + MOD) % MOD);
        return 0;
    }

    if(N == 1) {
        cout << (long long)((2*M-1) % MOD);
        return 0;
    }

    ll result = 2*M*(pow((ll)2, N-1)-1)%MOD + 4*M*(pow((ll)2, N-2)-1)%MOD + (4*M - 1) % MOD;
    result = (result + MOD) % MOD;

    cout << (long long)result;
}