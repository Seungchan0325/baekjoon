#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Q {
    ll a, b, k;
    Q(ll _a, ll _b, ll _k) : a(_a), b(_b), k(_k) {}
    bool operator < (const Q& other) const {
        return abs(a - b) > abs(other.a - other.b);
    }
};

ll N, A, B;
vector<Q> v;

int main()
{
    while(true) {
        cin >> N >> A >> B;
        if(N == 0 && A == 0 && B == 0) break;
        v.clear();
        for(ll i = 0; i < N; i++) {
            ll Da, Db, K;
            cin >> K >> Da >> Db;
            v.emplace_back(Da, Db, K);
        }
        sort(v.begin(), v.end());

        ll ans = 0;
        for(auto [a, b, k] : v) {
            ll x;
            if(a <= b) x = min(k, A);
            else x = k - min(k, B);
            ans += a * x;
            ans += b * (k - x);
            A -= x;
            B -= k - x;
        }
        cout << ans << "\n";
    }
}