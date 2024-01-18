#include <bits/stdc++.h>

using namespace std;

int cache[31][31];

int f(int n, int m) {
    if(n == 0) return 1;

    int& ret = cache[n][m];
    if(ret != -1) return ret;

    ret = 0;
    for(int leaves=n-1; leaves<=m-1; leaves++) {
        ret += f(n-1, leaves);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin>>t;
    memset(cache, -1, sizeof(cache));
    while(t--) {
        int n, m; cin>>n>>m;

        int result = f(n, m);
        cout<<result<<"\n";
    }
}