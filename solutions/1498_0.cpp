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

int main()
{
    string s;
    cin >> s;
    auto pi = getPartialMatch(s);
    for(int i = 0; i < s.size(); i++) {
        int len = i + 1 - pi[i];
        if(pi[i] == 0 || (i + 1) % len != 0) continue;
        cout << i + 1 << " " << (i + 1) / len << "\n";
    }
}