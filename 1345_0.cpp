#include <bits/stdc++.h>

using namespace std;

int n, arr[55];

int main() {
    cin >> n >> arr[0];
    for(int i = 1; i <= n; i++) cin >> arr[i];
    n++;

    double ans = INFINITY;

    bool zero = true;;
    for(int i = 1; i < n; i++) {
        if(arr[i-1] != arr[i]) zero = false;
    }
    if(zero) ans = 0;

    for(int i = 1; i < n; i++) {
        int d = arr[i] - arr[0];
        if(d < 0) goto not_found;

        bool is_possible = true;
        for(int j = 1; j < n; j++)
            if(arr[j] != arr[0] + j * d / i) {
                is_possible = false;
                break;
            }
        
        if(is_possible) ans = min(ans, (double)d / (double)i);
    }

    if(ans == INFINITY) goto not_found;

    cout << fixed;
    cout.precision(10);
    cout << ans;

    return 0;
not_found:
    cout << -1;
}