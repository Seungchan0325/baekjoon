#include <bits/stdc++.h>

using namespace std;

vector<int> getPartialMatch(const string& s)
{
    int n = s.size();
    vector<int> pi(n);

    int matched = 0;
    for(int i = 1; i < n; i++) {
        while(matched > 0 && s[i] != s[matched])
            matched = pi[matched - 1];
        
        if(s[i] == s[matched])
            pi[i] = ++matched;
    }
    return pi;
}

string kmp(const string& s, const string& a, const vector<int>& pi)
{
    int n = s.size();
    int m = a.size();

    int matched = 0;
    string ans;
    stack<int> stk;
    stk.push(0);
    for(int i = 0; i < n; i++) {
        ans.push_back(s[i]);
        while(matched > 0 && s[i] != a[matched])
            matched = pi[matched - 1];
        
        if(s[i] == a[matched])
            ++matched;
    
        stk.push(matched);
        if(matched == m) {
            for(int j = 0; j < m; j++) stk.pop(), ans.pop_back();
            matched = stk.top();
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int t;
    while(cin >> t) {
        string B;
        cin >> B;
        auto pi = getPartialMatch(B);
        cin.ignore();
        while(t--) {
            string s; getline(cin, s);
            cout << kmp(s, B, pi) << "\n";
        }
    }
}