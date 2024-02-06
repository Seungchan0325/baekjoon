#include <bits/stdc++.h>

using namespace std;

vector<int> getPartialMatch(const string& N)
{
    int m = N.size();
    vector<int> pi(m, 0);

    int matched = 0;
    for(int i = 1; i < m; i++) {
        while(matched > 0 && N[i] != N[matched])
            matched = pi[matched - 1];
        
        if(N[i] == N[matched])
            pi[i] = ++matched;
    }
    return pi;
}

vector<int> kmpSearch(const string& H, const string& N)
{
    int n = H.size(), m = N.size();
    vector<int> ret;
    vector<int> pi = getPartialMatch(N);

    ret.reserve(n);

    int matched = 0;
    for(int i = 0; i < n; i++) {
        while(matched > 0 && H[i] != N[matched])
            matched = pi[matched - 1];
        
        if(H[i] == N[matched]) {
            matched++;
            if(matched == m) {
                ret.push_back(i - m + 2);
                matched = pi[matched - 1];
            }
        }
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    while(true) {
        string s;
        getline(cin, s);
        if(s[0] == '.') break;

        int n = s.size();
        auto ans = getPartialMatch(s);

        int matched = ans.back();
        while(matched > 0 && n % (n - matched)) {
            matched = ans[matched - 1];
        }

        if(matched < 0) cout << 1 << "\n";
        else cout << n / (n - matched) << "\n";
    }
}