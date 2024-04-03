#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, k;
    int a[10] = {0, };
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    reverse(a, a + n);

    int cnt = 0;
    for(int i = 0; i < n; i++) {
        cnt += k / a[i];
        k %= a[i];
    }
    cout << cnt;
}