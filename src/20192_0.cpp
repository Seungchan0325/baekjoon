#include <bits/stdc++.h>

using namespace std;

int arr[300004];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin>>n;
    for(int i=0; i<n; i++) cin>>arr[i];
    int g = 1, a = 1;
    for(int i=1; i<n; i++) {
        if(arr[i]>arr[i-1] && !a) g++, a ^= 1;
        else if(arr[i]<arr[i-1] && a) g++, a ^= 1;
    }
    //cout<<g<<"\n";
    int ans = (int)ceil(log2(g));
    cout<<ans;
}