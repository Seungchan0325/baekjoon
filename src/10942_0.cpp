#include <bits/stdc++.h>

using namespace std;

int n, m, arr[2001], cache[2001][2001];

bool is_palindrome(int l, int r) {
    if(l >= r) return true;
    int& ret = cache[l][r];
    if(ret != -1) return ret;

    if(arr[l] == arr[r])
        ret = is_palindrome(l + 1, r - 1);
    else
        ret = false;

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(cache, -1, sizeof(cache));
    cin>>n;
    for(int i = 1; i <= n; i++) cin>>arr[i];

    cin>>m;
    while(m--) {
        int l, r; cin>>l>>r;

        int result = is_palindrome(l, r);
        cout<<result<<"\n";
    }
}