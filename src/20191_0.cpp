#include <bits/stdc++.h>

using namespace std;

vector<int> alpha[26];
string s, t;

int main() {
    cin >> s;
    cin >> t;

    for(int i = 0; i < t.size(); i++) alpha[t[i]-'a'].push_back(i);

    int cnt = 1;
    int last = -1;
    for(int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';

        if(alpha[c].empty()) goto FAILED;

        int idx = upper_bound(alpha[c].begin(), alpha[c].end(), last) - alpha[c].begin();
        last = alpha[c][idx];
        if(idx >= alpha[c].size()) {
            cnt++;
            last = alpha[c][0];
        }
    }

    cout << cnt;
    return 0;
FAILED:
    cout << -1;
}