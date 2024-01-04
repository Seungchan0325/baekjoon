#include <bits/stdc++.h>

using namespace std;

int n, arr[100005];

int main() {
    cin>>n;
    for(int i=0; i<n; i++) cin>>arr[i];

    int min_diff = 1e10;
    int x, y;
    int l = 0, r = n - 1;
    while(l < r) {
        if(abs(arr[l] + arr[r]) <= min_diff) {
            min_diff = abs(arr[l] + arr[r]);
            x = arr[l]; y = arr[r];
        }

        if(arr[l] + arr[r] > 0) {
            r--;
        } else {
            l++;
        }
    }

    cout<<x<<" "<<y;
}