#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    cin >> s;
    int n = s.size();
    bool flag = false;
    for(int i = 1; i < n; i++) {
        if(s[i-1] != s[i]) flag = true;
    }
    if(flag == false) {
        cout << "-1\n";
        return 0;
    }

    int i = 0;
    int j = n-1;
    bool isp = true;
    while(i < j) {
        if(s[i] != s[j]) isp = false;
        i++; j--;
    }
    if(isp) cout << n-1 << "\n";
    else cout << n << "\n";
}