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

int table[256];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int tc;
    cin >> tc;
    while(tc--) {
        string A, W, S;
        cin >> A;
        cin >> W;
        cin >> S;

        memset(table, -1, sizeof(table));
        for(int i = 0; i < A.size(); i++) {
            table[A[i]] = i;
        }

        int n = A.size();

        vector<int> ans;
        for(int i = 0; i < A.size(); i++) {
            if(kmpSearch(S, W).size() == 1) {
                ans.push_back(i);
            }

            for(int j = 0; j < W.size(); j++) {
                W[j] = A[(table[W[j]]+1)%n];
            }
        }

        if(ans.empty()) {
            cout << "no solution\n";
        } else if(ans.size() == 1) {
            cout << "unique: " << ans[0] << "\n";
        } else {
            cout << "ambiguous: ";
            for(auto i : ans) {
                cout << i << " ";
            }
            cout << "\n";
        }
    }
}