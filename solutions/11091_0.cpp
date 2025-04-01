#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    cin.ignore();
    while(t--) {
        string s;
        getline(cin, s);
        ull chk = 0;
        for(auto c : s) {
            c = tolower(c);
            if('a' <= c && c <= 'z')
                chk |= (1LL<<(c-'a'));
        }
        if(chk == (1LL<<26)-1) cout << "pangram\n";
        else {
            cout << "missing ";
            for(char i = 'a'; i <= 'z'; i++) {
                if(~chk & (1LL<<(i-'a')))
                    cout << i;
            }
            cout << "\n";
        }
    }
}