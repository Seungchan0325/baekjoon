#include <bits/stdc++.h>

using namespace std;

int n, arr[100005], cache[100005];

int lis(int start) {
    int& ret = cache[start + 1];
    
    if(ret != -1) return ret;

    ret = 0;
    for(int next = start + 1; next < n; next++)
        if(arr[start] < arr[next] || start == -1)
            ret = max(ret, lis(next) + 1);
    
    return ret;
}

int main() {
    cin>>n;
    for(int i=0; i<n; i++) cin>>arr[i];

    memset(cache, -1, sizeof(cache));
    int result = lis(-1);

    cout<<result;
}