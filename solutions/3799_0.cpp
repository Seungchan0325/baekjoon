#include <bits/stdc++.h>

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    int sum = 0;
    int mn = 1e9;
    for(int i = 1; i * i <= n; i++) {
        if(m <= i*i) {
            sum += i*i;
            mn = min(mn, i*i);
        }
    }
    if(sum)
        cout << sum << "\n";
    if(mn < 1e9)
        cout << mn << "\n";
    else
        cout << "-1\n";
}
