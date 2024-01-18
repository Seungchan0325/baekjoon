#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10;
const int MAXM = 55;

int n, m, p[MAXN];
bool visited[MAXM];
string cache[MAXM];

bool cmp(const string& a, const string& b) {
    if(a[0] == '0') return true;
    else if(b[0] == '0') return false;
    if(a.size() != b.size()) return a.size() < b.size();

    for(int i = 0; i < a.size(); ++i) {
        if(a[i] != b[i]) return a[i] < b[i];
    }

    return false;
}

string dp(int money) {
    string& ret = cache[money];
    if(visited[money]) return ret;
    visited[money] = true;

    ret = "";
    for(int i = 0; i < n; ++i) {
        if(money < p[i]) continue;
        ret = max(dp(money-p[i])+to_string(i), ret, cmp);
    }

    return ret;
}

int main() {
    cin >> n;
    for(int i = 0; i < n; ++i) cin >> p[i];
    cin >> m;

    string result = dp(m);
    string out;
    bool flag = false;
    for(auto c : result)
        if(flag || c != '0') {
            out.push_back(c);
            flag = true;
        }
    if(out.empty()) out = '0';
    cout << out;
}