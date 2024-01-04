#include <bits/stdc++.h>

using namespace std;

int cache[20][20][20];

int dp(int a, int b, int c)
{
    if(a == 0 && b == 0 && c == 0) return 1;
    int& ret = cache[a][b][c];
    ret = 0;
    if(0 < a) ret += dp(a - 1, b, c);
    if(0 < b) ret += dp(a, b - 1, c);
    if(0 < c) ret += dp(a, b, c - 1);
    return ret;
}

int main()
{
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    cout << dp(a, b, c);
}
Unknown problem. sumbmit number: 70656937