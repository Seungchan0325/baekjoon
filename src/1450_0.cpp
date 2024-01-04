#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n, k, arr[45];

void f(vector<ll>& v, int idx, int end, ll sum) {
    if(idx == end) {
        v.push_back(sum);
        return;
    }

    f(v, idx+1, end, sum);
    f(v, idx+1, end, sum + arr[idx]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for(int i = 0; i < n; i++) cin >> arr[i];

    vector<ll> l, r;
    f(l, 0, n/2, 0);
    f(r, n/2, n, 0);

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    ll ans = 0;
    for(auto w : l) {
        ans += upper_bound(r.begin(), r.end(), k - w) - r.begin();
    }
    cout << ans;
}