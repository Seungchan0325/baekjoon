#include <bits/stdc++.h>

using namespace std;

int n, ans[303030];

int main()
{
    cin >> n;
    if(n == 1) {
        cout << "-1";
        return 0;
    }
    for(int i = 1; i <= n; i++) {
        if(i == 1) {
            cout << 1 << " " << 2*n+1 << " " << 2*n-1 << " ";
        } else if(i == n) {
            cout << 2*n << " " << 2 << " " << 3*n << " ";
        } else {
            cout << i+1 << " " << 2*n+i << " " << 2*n-i << " ";
        }
    }
}
