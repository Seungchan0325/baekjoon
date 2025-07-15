#include <bits/stdc++.h>

using namespace std;

bool solve(string s)
{
    long long move, cnt; move = cnt = 0;
    reverse(s.begin(), s.end());
    char cur = '.';

    for(auto c : s) {
        if(cur == '.') cur = c;
        if(cur == '.') continue;
        if(c == '.') move += (cur == 'W' ? +1 : -1) * cnt;
        else if(c == cur) cnt++;
        else cur = '.', cnt = 0;
    }
    return move > 0;
}

int main()
{
    int t; cin >> t;
    while(t--) {
        string s; cin >> s;
        cout << (solve(s) ? "WHITE" : "BLACK") << "\n";
    }
}