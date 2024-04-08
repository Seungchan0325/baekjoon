#include <bits/stdc++.h>

using namespace std;

int n, m;
string s;

int main()
{
    cin >> n >> m >> s;

    int ans = 0;
    int cnt = 0;
    for(int i = 2; i < m; i += 2) {
        if(s.substr(i-2, 3) == "IOI") cnt++;
        else cnt = 0;
        if(s[i] == 'I' && cnt >= n) ans++;
    }

    cnt = 0;
    for(int i = 3; i < m; i += 2) {
        if(s.substr(i-2, 3) == "IOI") cnt++;
        else cnt = 0;
        if(s[i] == 'I' && cnt >= n) ans++;
    }

    cout << ans;
}