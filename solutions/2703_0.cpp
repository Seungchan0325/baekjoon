#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--) {
        string s;
        cin.ignore();
        getline(cin, s);
        char table[26];
        for(int i = 0; i < 26; i++) {
            cin >> table[i];
        }
        for(auto c : s) {
            if(c == ' ') cout << " ";
            else cout << table[c-'A'];
        }
        cout << "\n";
    }
}