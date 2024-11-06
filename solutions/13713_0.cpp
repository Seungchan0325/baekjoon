#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll M1 = 320;
const ll P1 = 99999323;
const ll M2 = 764;
const ll P2 = 99999217;

const ll MAXN = 1000005;

ll N, K, H1[MAXN], H2[MAXN], pw1[MAXN], pw2[MAXN], inv1[MAXN], inv2[MAXN];
string s;

ll pw(ll x, ll n, ll mod)
{
    if(n == 0) return 1;
    if(n & 1) return x * pw(x, n-1, mod) % mod;
    ll half = pw(x, n/2, mod);
    return half * half % mod;
}

bool f(int i, ll len)
{
    ll h1 = (H1[i] - H1[i-len] + P1) * inv1[i-len+1] % P1;
    ll h2 = (H2[i] - H2[i-len] + P2) * inv2[i-len+1] % P2;
    ll h3 = (H1[N] - H1[N-len] + P1) * inv1[N-len+1] % P1;
    ll h4 = (H2[N] - H2[N-len] + P2) * inv2[N-len+1] % P2;
    return tie(h1, h2) == tie(h3, h4);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> s;
    N = s.size();
    s = " " + s;
    pw1[0] = pw2[0] = 1;
    for(int i = 1; i <= N; i++) {
        pw1[i] = pw1[i-1] * M1 % P1;
        pw2[i] = pw2[i-1] * M2 % P2;
    }
    inv1[N] = pw(pw1[N], P1-2, P1);
    inv2[N] = pw(pw2[N], P2-2, P2);
    for(int i = N-1; i >= 1; i--) {
        inv1[i] = inv1[i+1] * M1 % P1;
        inv2[i] = inv2[i+1] * M2 % P2;
    }
    for(int i = 1; i <= N; i++) {
        H1[i] = (H1[i-1] + s[i] * pw1[i]) % P1;
        H2[i] = (H2[i-1] + s[i] * pw2[i]) % P2;
    }

    int Q;
    cin >> Q;

    while(Q--) {
        int i; cin >> i;
        int lo = 0;
        int hi = i+1;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(f(i, mid)) lo = mid;
            else hi = mid;
        }
        cout << lo << '\n';
    }
}