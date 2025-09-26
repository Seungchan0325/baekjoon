#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t; cin >> t;
    while(t--) {
        int n, k;
        cin >> n >> k;
        if(n == k) cout << (k+1)/2 << "\n";
        else cout << min(2*k, n) << "\n";
    }
}