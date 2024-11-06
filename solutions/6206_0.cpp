#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll M1 = 320;
const ll P1 = 99999323;
const ll M2 = 764;
const ll P2 = 99999217;

const ll MAXN = 20005;

ll N, K, H1[MAXN], H2[MAXN], pw1[MAXN], pw2[MAXN], s[MAXN];

ll pw(ll x, ll n, ll mod)
{
    if(n == 0) return 1;
    if(n & 1) return x * pw(x, n-1, mod) % mod;
    ll half = pw(x, n/2, mod);
    return half * half % mod;
}

ll appear(ll len)
{
    map<pair<ll, ll>, int> cnt;
    for(int i = 1; i + len - 1 <= N; i++) {
        ll h1 = (H1[i+len-1] - H1[i-1] + P1) * pw(pw1[i], P1-2, P1) % P1;
        ll h2 = (H2[i+len-1] - H2[i-1] + P2) * pw(pw2[i], P2-2, P2) % P2;
        cnt[{h1, h2}]++;
    }
    int mx = -1;
    for(auto &p : cnt) mx = max(mx, p.second);
    return mx;
}

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) cin >> s[i];
    pw1[0] = pw2[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        pw1[i] = pw1[i-1] * M1 % P1;
        pw2[i] = pw2[i-1] * M2 % P2;
    }
    for(int i = 1; i <= N; i++) {
        H1[i] = (H1[i-1] + s[i] * pw1[i]) % P1;
        H2[i] = (H2[i-1] + s[i] * pw2[i]) % P2;
    }

    int lo = 0;
    int hi = N;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(appear(mid) >= K) lo = mid;
        else hi = mid;
    }

    cout << lo;
}