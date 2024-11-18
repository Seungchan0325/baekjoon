#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll N, M;

int main()
{
    cin >> N >> M;
    vector<pair<ll, ll>> v;
    for(ll i = 1; i <= N; i++) {
        ll a;
        cin >> a;
        v.emplace_back(a+i*M, -a+i*M);
    }
    sort(v.begin(), v.end());
    vector<ll> lis;
    for(auto [a, b] : v) {
        if(lis.empty() || lis.back() <= b) lis.push_back(b);
        else *upper_bound(lis.begin(), lis.end(), b) = b;
    }
    cout << N - lis.size();
}