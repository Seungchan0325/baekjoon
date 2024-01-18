#include <bits/stdc++.h>

using namespace std;

int k, n, a;


bool stop = false;
void gen(string s) {
    if(stop) return;
    for(int len = 1; len < s.size(); len++) {
        auto ss = s.substr(s.size()-len);
        int cnt = 0;
        for(int i = 1; i <= k && i*len <= s.size(); i++)
            if(s.substr(s.size() - i*len, len) == ss) cnt++;
        if(k <= cnt) return;
    }

    if(s.size() == n) {
        stop = true;
        cout << s;
        return;
    }

    for(int i = 0; i < a; i++) gen(s + (char)('A'+i));
}

int main() {
    cin >> k >> n >> a;
    gen("");
    if(!stop) cout << -1;
}