#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll M1 = 533;
const ll M2 = 325;
const ll P1 = 999999391;
const ll P2 = 999999223;

const int MAXN = 202020;

string s1, s2;
ll pw1[MAXN], pw2[MAXN], inv1[MAXN], inv2[MAXN];
ll h1[MAXN], h2[MAXN];
ll hp1[MAXN], hp2[MAXN];

ll pw(ll x, ll n, ll mod)
{
    if(n == 0) return 1;
    if(n&1) return pw(x, n-1, mod) * x % mod;
    ll half = pw(x, n/2, mod);
    return half * half % mod;
}

int chk(int l)
{
    vector<pair<ll, ll>> v1;
    for(int i = 0; i + l < s1.size(); i++) {
        ll a = (h1[i+l]-h1[i]+P1)%P1*inv1[i+1] % P1;
        ll b = (hp1[i+l]-hp1[i]+P2)%P2*inv2[i+1] % P2;
        v1.emplace_back(a, b);
        // v1.push_back((h1[i+l]-h1[i]+P1)%P1*pw(pw(M1, i+1, P1), P1-2, P1) % P1);
    }
    
    sort(v1.begin(), v1.end());
    for(int i = 0; i + l < s2.size(); i++) {
        ll a = (h2[i+l]-h2[i]+P1)%P1*inv1[i+1] % P1;
        ll b = (hp2[i+l]-hp2[i]+P2)%P2*inv2[i+1] % P2;
        if(binary_search(v1.begin(), v1.end(), pair(a, b))) return i+1;
    }

    return -1;
}

int main()
{
    pw1[0] = pw2[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        pw1[i] = pw1[i-1] * M1 % P1;
        pw2[i] = pw2[i-1] * M2 % P2;
    }
    inv1[MAXN-1] = pw(pw1[MAXN-1], P1-2, P1);
    inv2[MAXN-1] = pw(pw2[MAXN-1], P2-2, P2);
    for(int i = MAXN-2; i >= 0; i--) {
        inv1[i] = inv1[i+1] * M1 % P1;
        inv2[i] = inv2[i+1] * M2 % P2;
    }
    cin >> s1 >> s2;
    s1 = " " + s1;
    s2 = " " + s2;
    for(int i = 1; i < s1.size(); i++) {
        h1[i] = (h1[i-1] + s1[i] * pw1[i]) % P1;
        hp1[i] = (hp1[i-1] + s1[i] * pw2[i]) % P2;
    }
    for(int i = 1; i < s2.size(); i++) {
        h2[i] = (h2[i-1] + s2[i] * pw1[i]) % P1;
        hp2[i] = (hp2[i-1] + s2[i] * pw2[i]) % P2;
    }

    int lo = 0;
    int hi = min(s1.size(), s2.size());
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(chk(mid) != -1) lo = mid;
        else hi = mid;
    }
    cout << lo << "\n";
    int s = chk(lo);
    cout << s2.substr(s, lo) << "\n";
}