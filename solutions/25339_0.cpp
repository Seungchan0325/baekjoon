#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    int ans = 0;
    while(q--) {
        int a, l, r;
        cin >> a >> l >> r;
        if(a == 1) {
            ans ^= 1;
        } else {
            int a = r - l;
            ans ^= (a*(a+1)/2)&1;
        }
        cout << ans << "\n";
    }
}