#include <bits/stdc++.h>

using namespace std;

int a[33][33];

int main()
{
    int n = 30;
    for(int i = 1; i <= n/2; i++) a[n/2][i] = 1;
    for(int i = 1; i < n/2; i++) a[i][n/2] = n/2;
    for(int i = n/2+1; i <= n; i++) a[n/2+1][i] = n*n/4;
    for(int i = n/2+2; i <= n; i++) a[i][n/2+1] = n*n*n/8;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}