#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n;
    cin >> n;
    long long ans = 1;

    if(n <= 3) {
        cout << n;
        return 0;
    }

    while(n % 3 != 0) {
        ans *= 2;
        n -= 2;
    }

    for(int i = 0; i < n / 3; i++) {
        ans *= 3;
        ans %= 10007;
    }

    cout << ans;
}