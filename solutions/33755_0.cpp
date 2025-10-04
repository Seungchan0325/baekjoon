#include <bits/stdc++.h>

using namespace std;

const int MAXN = 303030;

int n, a[MAXN], pre[MAXN], suf[MAXN];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) pre[i] = max(pre[i-1]+a[i], a[i]);
    for(int i = n; i >= 1; i--) suf[i] = max(suf[i+1]+a[i], a[i]);
    for(int i = 1; i <= n; i++) {
        cout << pre[i] + suf[i] - a[i] << " ";
    }
}