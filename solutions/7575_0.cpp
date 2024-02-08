#include <bits/stdc++.h>

using namespace std;

vector<int> getPartialMatch(const vector<int>& N)
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

vector<int> kmpSearch(const vector<int>& H, const vector<int>& N)
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
    int N, K;
    cin >> N >> K;
    vector<int> M(N);
    vector<vector<int>> v(N);
    for(int i = 0; i < N; i++) {
        cin >> M[i];
        v[i].resize(M[i]);
        for(int j = 0; j < M[i]; j++) {
            cin >> v[i][j];
        }
    }

    for(int start = 0; start <= M[0] - K; start++) {
        for(int end = start + K; end <= M[0]; end++) {
            vector<int> vv(v[0].begin() + start, v[0].begin() + end);
            vector<int> rvv(vv);
            reverse(rvv.begin(), rvv.end());

            for(int i = 1; i < N; i++) {
                if(kmpSearch(v[i], vv).empty() && kmpSearch(v[i], rvv).empty()) {
                    goto EXIT_LOOP;
                }
            }
            goto FOUND;
        }
EXIT_LOOP: {}
    }

    goto NOT_FOUND;

FOUND:
    cout << "YES\n";
    return 0;
NOT_FOUND:
    cout << "NO\n";
    return 0;
}