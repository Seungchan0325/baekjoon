#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--) {
        string s;
        cin >> s;
        map<char, int> m;
        for(auto c : s) m[c]++;
        int n;
        cin >> n;
        while(n--) {
            string a;
            cin >> a;
            bool possible = true;
            for(auto c : a) {
                m[c]--;
                if(m[c] < 0) possible = false;
            }
            for(auto c : a) m[c]++;
            if(possible) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}