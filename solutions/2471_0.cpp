#include <bits/stdc++.h>

using namespace std;

int n;
string s;
int k;

bool compare(string a, string b) {
    int i, j;
    i = j = 0;
    while(i < a.size() || j < b.size()) {
        while(i < a.size() && (a[i] == '(' || a[i] == ')')) i++;
        while(j < b.size() && (b[j] == '(' || b[j] == ')')) j++;
        if(a[i] != b[j]) return a[i] < b[j];
        i++; j++;
    }
    return false;
}

bool same(string a, string b)
{
    return !compare(a, b) && !compare(b, a);
}

vector<string> cache[202][202];

vector<string> f(int l, int r)
{
    if(cache[l][r].size()) return cache[l][r];
    vector<string> s1, s2;
    s1.push_back("");
    s2.push_back("");
    stack<int> stk;
    for(int i = l; i <= r; i++) {
        if(s[i] == '(')
            stk.push(i);
        else if(s[i] == ')') {
            if(stk.size() == 1) {
                auto sts = f(stk.top() + 1, i - 1);
                vector<string> nxt;
                for(int j = 0; j < s1.size(); j++) {
                    for(int k = 0; k < sts.size(); k++) {
                        nxt.push_back(s1[j] + sts[k]);
                    }
                }
                sort(nxt.begin(), nxt.end(), compare);
                nxt.erase(unique(nxt.begin(), nxt.end(), same), nxt.end());
                s1.clear();
                for(int j = 0; j < min<int>(nxt.size(), 1000); j++) s1.push_back(nxt[j]);
            }
            stk.pop();
        }
        else if(stk.empty()) {
            for(auto& ss : s1) ss.push_back(s[i]);
        }
    }
    
    for(int i = r; i >= l; i--) {
        if(s[i] == ')') stk.push(i);
        else if(s[i] == '(') {
            if(stk.size() == 1) {
                auto sts = f(i + 1, stk.top() - 1);
                vector<string> nxt;
                for(int j = 0; j < s2.size(); j++) {
                    for(int k = 0; k < sts.size(); k++) {
                        nxt.push_back(s2[j] + sts[k]);
                    }
                }
                sort(nxt.begin(), nxt.end(), compare);
                nxt.erase(unique(nxt.begin(), nxt.end(), same), nxt.end());
                s2.clear();
                for(int j = 0; j < min<int>(nxt.size(), 1000); j++) s2.push_back(nxt[j]);
            }
            stk.pop();
        }
        else if(stk.empty()) {
            for(auto& ss : s2) ss.push_back(s[i]);   
        }
    }

    cache[l][r].insert(cache[l][r].end(), s1.begin(), s1.end());
    cache[l][r].insert(cache[l][r].end(), s2.begin(), s2.end());
    sort(cache[l][r].begin(), cache[l][r].end(), compare);
    cache[l][r].erase(unique(cache[l][r].begin(), cache[l][r].end(), same), cache[l][r].end());
    while(cache[l][r].size() > 1000) cache[l][r].pop_back();
    return cache[l][r];
}

int main()
{
    cin >> s;
    cin >> k;

    n = s.size();
    auto ans = f(0, n-1);
    if(ans.size() < k) cout << "NO\n";
    else cout << ans[k-1] << "\n";
}