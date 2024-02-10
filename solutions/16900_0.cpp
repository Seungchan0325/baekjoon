#include <bits/stdc++.h>

using namespace std;

using ll = long long;

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

int main()
{
    int k;
    string s;
    cin >> s >> k;

    auto pi = getPartialMatch(s);
    ll result = s.size() + (ll)(k - 1) * (s.size() - pi.back());
    cout << result;
}