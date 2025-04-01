#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<string> s(n);
    for(auto& i : s) cin >> i;
    sort(s.begin(), s.end());
    int ans = n;
    for(int i = 1; i < n; i++) {
        int p = 0;
        while(p < s[i].size() && p < s[i-1].size() && s[i][p] == s[i-1][p]) p++;
        if(p == s[i].size() || p == s[i-1].size()) ans--;
    }
    cout << ans;
}