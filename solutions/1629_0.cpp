#include <bits/stdc++.h>

using namespace std;

using llint = long long int;

llint pow(llint a, llint n, llint mod)
{
    if(n == 0) return 1;
    if(n & 1) return (pow(a, n-1, mod) * a) % mod;
    llint half = pow(a, n/2, mod);
    return (half * half) % mod;
}

int main()
{
    llint a, b, c;
    cin >> a >> b >> c;
    llint result = pow(a, b, c);
    cout << result;
}