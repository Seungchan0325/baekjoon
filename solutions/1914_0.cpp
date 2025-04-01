#include <bits/stdc++.h>

using namespace std;

void compute(int n, int a, int b, int c)
{
    if(n == 1) {
        cout << a << " " << c << "\n";
        return;
    }
    compute(n-1, a, c, b);
    cout << a << " " << c << "\n";
    compute(n-1, b, a, c);
}

int main()
{
    int n;
    cin >> n;
    __int128_t step = ((__int128_t(1))<<n) - 1;
    string s;
    while(step) {
        s += '0' + step % 10;
        step /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s << "\n";
    if(n <= 20) {
        compute(n, 1, 2, 3);
    }
}