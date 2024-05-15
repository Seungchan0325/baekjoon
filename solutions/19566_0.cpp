#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 200005;

ll N, K, A[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;

    ll prv = 0;
    map<ll, ll> m;
    m[0]++;
    for(ll i = 1; i <= N; i++) {
        ll Ai;
        cin >> Ai;
        Ai -= K;
        Ai += prv;
        prv = Ai;
        m[Ai]++;
    }

    ll cnt = 0;
    for(auto [k, v] : m) {
        cnt += (ll)v*(v-1)/2;
    }

    cout << cnt;
}