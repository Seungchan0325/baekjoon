#include <bits/stdc++.h>

using namespace std;
#define int long long
signed main()
{
    string s;
    cin >> s;
    int ans = 0;
    int t = 0;
    char prv = '#';
    for(auto c : s) {
        if(c == '(') t++;
        else {
            t--;
            if(prv == '(') ans += t;
        }
        prv = c;
    }
    cout << ans;
}