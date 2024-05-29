#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    while(true) {
        string s;
        cin >> s;
        if(s == "0") break;

        ll halfsz = (s.size()+1)/2;
        ll half;

        string tmp = s.substr(0, halfsz);
        reverse(tmp.begin(), tmp.end());
        if(stoll(tmp) >= stoll(s.substr(s.size()/2))) half = stoll(s.substr(0, halfsz));
        else half = stoll(s.substr(0, halfsz)) + 1;

        tmp.clear();
        for(int i = 0; i < halfsz; i++) {
            tmp.push_back('0' + half%10);
            half /= 10;
        }
        reverse(tmp.begin(), tmp.end());
        if(s.size()&1) {
            string tt = tmp;
            tmp.insert(tmp.end(), tt.rbegin()+1, tt.rend());
        } else {
            string tt = tmp;
            tmp.insert(tmp.end(), tt.rbegin(), tt.rend());
        }

        ll ans = stoll(tmp) - stoll(s);
        cout << ans << "\n";
    }
}