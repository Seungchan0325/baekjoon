#include <bits/stdc++.h>

using namespace std;

string rainbow = "ROYGBIV";

int main()
{
    int n;
    cin >> n;
    set<char> s;
    for(int i = 0; i < n; i++) {
        char c;
        cin >> c;
        s.insert(c);
    }

    bool small_possible = true;
    bool big_possible = true;
    for(char c : rainbow) {
        if(s.count(tolower(c)) == 0) {
            small_possible = false;
        }

        if(s.count(toupper(c)) == 0) {
            big_possible = false;
        }
    }

    if(small_possible && big_possible) cout << "YeS";
    else if(small_possible) cout << "yes";
    else if(big_possible) cout << "YES";
    else cout << "NO!";
}