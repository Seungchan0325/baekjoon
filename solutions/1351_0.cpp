#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n, p, q;
map<ll, ll> cache;

ll f(ll i) {
    if(i == 0) return 1;
    if(cache.contains(i)) return cache[i];

    cache[i] = f(i/p) + f(i/q);

    return cache[i];
}

int main() {
    cin >> n >> p >> q;
    ll result = f(n);
    cout << result;
}