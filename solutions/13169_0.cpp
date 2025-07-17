#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

int n;
ll a[MAXN];

void bruteforce(int i, int e, ll s, vector<ll>& v)
{
    if(i >= e) {
        v.push_back(s);
        return;
    }
    bruteforce(i+1, e, s, v);
    bruteforce(i+1, e, s+a[i], v);
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    vector<ll> front, back;
    bruteforce(0, n/2, 0, front);
    bruteforce(n/2, n, 0, back);
    sort(front.begin(), front.end());
    sort(back.begin(), back.end());

    ll ans = 0;
    for(int k = 40; k >= 0; k--) {
        sort(front.begin(), front.end());
        for(ll i : back) {
            int m = lower_bound(front.begin(), front.end(), (1LL<<(k+1))-i) - front.begin();
            int j;
            j = lower_bound(front.begin(), front.begin()+m, (1LL<<k)-i) - front.begin();
            if((m-j)%2) ans ^= (1LL<<k);
            j = lower_bound(front.begin()+m, front.end(), 3*(1LL<<k)-i) - front.begin();
            int l = lower_bound(front.begin() + m, front.end(), 3*(1LL<<k)-i) - front.begin();
            int r = lower_bound(front.begin() + m, front.end(), (1LL<<(k+2))-i) - front.begin();
            if(l<r && (r-l)%2) ans ^= (1LL<<k);
        }
        ll mask = (1LL<<k)-1;
        for(auto& i : front) i &= mask;
        for(auto& i : back) i &= mask;
    }

    cout << ans << "\n";
}