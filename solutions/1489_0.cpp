#include <bits/stdc++.h>

using namespace std;

int n, a[50], b[50], cache[50][50];

int dp(int p1, int p2)
{
    if(p1 == n) return 0;

    int& ret = cache[p1][p2];
    if(ret != -1) return ret;

    int score = 0;
    if(a[p1] == b[p2]) score = 1;
    else if(a[p1] > b[p2]) score = 2;

    ret = max(dp(p1 + 1, p2), dp(p1 + 1, p2 + 1) + score);
    return ret;
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < n; i++)
        cin >> b[i];

    sort(a, a + n);
    sort(b, b + n);

    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0);
    cout << result;
}