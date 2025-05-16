#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_cxx;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    string s;
    cin >> s;
    crope r(s.c_str());
    int q; cin >> q;
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int x, y; cin >> x >> y;
            auto ss = r.substr(x, y-x+1);
            r.erase(x, y-x+1);
            r.insert(0, ss);
        } else if(op == 2) {
            int x, y; cin >> x >> y;
            auto ss = r.substr(x, y-x+1);
            r.erase(x, y-x+1);
            r.insert(r.size(), ss);
        } else {
            int x; cin >> x;
            char s = r.at(x);
            cout << s << "\n";
        }
        // for(auto c : r) {
        //     cout << c;
        // }
        // cout << "\n";
    }
}