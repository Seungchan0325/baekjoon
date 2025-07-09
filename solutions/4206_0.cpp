#include <bits/stdc++.h>

using namespace std;

using ll = __int128_t;

ll dp[101];
string s[27];

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
                ret.push_back(i - m + 1);
                matched = pi[matched - 1];
            }
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    s[0] = '0';
    s[1] = '1';
    for(int i = 2; i < 27; i++) {
        s[i] = s[i-1] + s[i-2];
    }

    int iter = 0;
    int n;
    while(cin >> n) {
        string p; cin >> p;
        for(int i = 0; i < 27; i++)
            dp[i] = kmpSearch(s[i], p).size();

        string p1 = s[25].substr(0, ssize(p));
        string s1 = s[25].substr(ssize(s[25])-ssize(p));
        string p2 = s[26].substr(0, ssize(p));
        string s2 = s[26].substr(ssize(s[26])-ssize(p));
        string p3, s3;
        for(int i = 27; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
            auto v = kmpSearch(s2+p1, p);
            dp[i] += lower_bound(v.begin(), v.end(), ssize(s2)) - lower_bound(v.begin(), v.end(), ssize(s2)-ssize(p)+1);
            p3 = p2;
            s3 = s1;
            p1 = p2;
            s1 = s2;
            p2 = p3;
            s2 = s3;
        }

        iter++;
        cout << "Case " << iter << ": ";
        cout << (unsigned long long)dp[n] << "\n";
    }
}