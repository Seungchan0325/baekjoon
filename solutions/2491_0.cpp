#include <bits/stdc++.h>

using namespace std;

int n, arr[100005];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=0; i<n; i++) cin>>arr[i];

    int ans = 1;
    int count1 = 1;
    int count2 = 1;
    for(int i=1; i<n; i++) {
        if(arr[i] < arr[i-1])
            count1 = 0;
        if(arr[i-1] < arr[i])
            count2 = 0;
        count1++; count2++;
        ans = max(ans, max(count1, count2));
    }

    cout<<ans;
}