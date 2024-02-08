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
                ret.push_back(i - m + 1);
                matched = pi[matched - 1];
            }
        }
    }

    return ret;
}

const int MAXL = 100005;
const int MAXN = 505;

int n, dp[MAXL], lenght[MAXN];
bool table[MAXL][MAXN];
string s;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> s;
    cin >> n;
    for(int i = 0; i < n; i++) {
        string ss;
        cin >> ss;
        lenght[i] = ss.size();
        auto v = kmpSearch(s, ss);
        for(int j : v) {
            int idx = j + ss.size();
            table[idx][i] = true;
        }
    }

    for(int i = 1; i <= s.size(); i++) {
        dp[i] = dp[i - 1];
        for(int j = 0; j < n; j++) {
            if(!table[i][j]) continue;
            int cand = dp[i - lenght[j]] + lenght[j];
            dp[i] = max(cand, dp[i]);
        }
    }
    cout << dp[s.size()];
}