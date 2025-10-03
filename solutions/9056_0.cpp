#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t; cin >> t;
    while(t--) {
        string a, b;
        cin >> a >> b;
        map<char, int> m;
        bool yes = true;
        for(auto c : b) {
            if(a.find(c) == a.npos) yes = false;
            m[c]++;
        }
        for(auto c : a) {
            if(m[c] <= 0) yes = false;
        }
        if(yes) cout << "YES\n";
        else cout << "NO\n";
    }
}