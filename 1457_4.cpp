#include <bits/stdc++.h>

using namespace std;

const int AB = 1e7 + 1e6;

int a, b, n;

int main()
{
    cin >> a >> b >> n;
    int ab = a + b;

    int cnt = 0;
    for(int i = 2; i <= ab; i++)
    {
        if(a <= i && i <= ab) cnt--;
        int _pow = pow(i, n);
        cnt += (ab / i - (a - 1) / i);
        cnt -= (ab / _pow - (a - 1) / _pow);
    }
    cout << cnt;
}