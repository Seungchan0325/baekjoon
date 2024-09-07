#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Ans {
    ll k, m;
    vector<ll> ans;
};

pair<ll, ll> count_zeros(ll n, ll base)
{
    ll zeros = 0;
    ll len = 0;
    while(n) {
        if(n%base == 0) zeros++;
        n /= base;
        len++;
    }
    return {zeros, len};
}

Ans solve(ll n)
{
    Ans ret;
    ll& k = ret.k;
    ll& m = ret.m;
    vector<ll>& ans = ret.ans;
    
    k = 0;
    m = 0;

    for(ll i = 2; i <= n; i++) {
        auto [zeros, len] = count_zeros(n, i);

        if(len <= k) break;

        if(zeros > k) {
            ans.clear();
            k = zeros;
            m = 1;
            ans.push_back(i);
        } else if(zeros == k) {
            ans.push_back(i);
            m++;
        }
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int tc;
    cin >> tc;

    unordered_map<ll, Ans> m;
    while(tc--) {
        ll n;
        cin >> n;

        if(!m.count(n)) {
            m[n] = solve(n);
        }

        Ans& ans = m[n];
        cout << ans.k << " " << ans.m << "\n";
        for(auto i : ans.ans) cout << i << " ";
        cout << "\n";
    }
}