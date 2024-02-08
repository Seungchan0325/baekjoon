#include <bits/stdc++.h>

using namespace std;

using ll = long long;

vector<ll> getPartialMatch(const string& N)
{
    ll m = N.size();
    vector<ll> pi(m, 0);

    ll matched = 0;
    for(ll i = 1; i < m; i++) {
        while(matched > 0 && N[i] != N[matched])
            matched = pi[matched - 1];
        
        if(N[i] == N[matched])
            pi[i] = ++matched;
    }
    return pi;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll n;
    cin >> n;
    string s;
    cin >> s;

    ll sum = 0;
    auto pi = getPartialMatch(s);
    for(ll i = 0; i < n; i++) {
        ll matched = pi[i];
        while(matched > 0 && pi[matched - 1] > 0)
            matched = pi[matched - 1];
        pi[i] = matched;
        if(matched > 0 && matched <= i - matched + 1) {
            sum += i - matched + 1;
        }
    }
    cout << sum;
}