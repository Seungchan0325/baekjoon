#include <bits/stdc++.h>

using namespace std;

int n, arr[2005], taken[2005][2005];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> arr[i];

    sort(arr, arr + n);

    int ans = 0;

    for(int i = 0; i < n; i++) {
        int cnt = upper_bound(arr, arr + n, arr[i]) - lower_bound(arr, arr + n, arr[i]);
        ans = max(ans, cnt);
    }

    n = unique(arr, arr + n) - arr;

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int diff = arr[j] - arr[i];

            int prev_idx = lower_bound(arr, arr + n, arr[i] - diff) - arr;
            
            if(arr[prev_idx] != arr[i] - diff) taken[i][j] = 2;
            else taken[i][j] = taken[prev_idx][i] + 1;
            ans = max(ans, taken[i][j]);
        }
    }

    cout << ans;
}