#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

int n;
vector<string> v;

int main() {
    cin >> n;
    v.resize(n);
    for(auto& s : v) cin >> s;

    for(int i = 0; i < v[0].size(); i++) {
        bool flag = false;
        for(auto& s : v) if(s[i] != v[0][i]) flag = true;
        if(flag) cout << '?';
        else cout << v[0][i];
    }
}