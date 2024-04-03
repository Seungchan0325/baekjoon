#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    n = 1000 - n;

    int cnt = 0;
    for(auto coin : {500, 100, 50, 10, 5, 1}) {
        cnt += (n / coin);
        n %= coin;
    }
    cout << cnt;
}