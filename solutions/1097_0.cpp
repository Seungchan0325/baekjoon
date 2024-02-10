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
    for(int i = 1; i < n; i++) {
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
    int n, k;
    cin >> n;
    vector<pair<string, int>> words(n);
    for(int i = 0; i < n; i++) {
        cin >> words[i].first;
        words[i].second = i;
    }
    cin >> k;

    int ans = 0;
    sort(words.begin(), words.end());
    do {
        string s;
        for(auto& [ss, idx] : words) s += ss;
        int cnt = kmpSearch(s + s, s).size();
        if(cnt == k) ans++;
    } while(next_permutation(words.begin(), words.end()));
    cout << ans;
}