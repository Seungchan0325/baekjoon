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
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int> aa(n), bb(n);
    for(int i = 0; i < n - 1; i++) {
        aa[i] = a[i + 1] - a[i];
        bb[i] = b[i + 1] - b[i];
    }
    aa[n - 1] = 360000 + a[0] - a[n - 1];
    bb[n - 1] = 360000 + b[0] - b[n - 1];

    aa.insert(aa.end(), aa.begin(), aa.end());

    if(kmpSearch(aa, bb).empty()) cout << "impossible";
    else cout << "possible";
}