#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

ll n, s, ans;
vector<ll> S, l, r;

void f(vector<ll>& v, int idx, int end, ll sum) {
    if(idx >= end) {
        v.push_back(sum);
        return;
    }

    f(v, idx + 1, end, sum);
    f(v, idx + 1, end, sum + S[idx]);
}

int main() {
    cin>>n>>s;
    S.resize(n);
    for(int i=0; i<n; i++) cin>>S[i];

    // f(l, 0, n/2, 0);
    // f(r, n/2, n, 0);

    f(l, 0, min(20LL, n), 0);
    f(r, 20, n, 0);

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    for(ll x : l) {
        ans += upper_bound(r.begin(), r.end(), s - x) - lower_bound(r.begin(), r.end(), s - x);
    }

    if(s == 0) ans--;

    cout<<ans;
}