#pragma GCC optimize("O3", "Ofast", "unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

using ll = long long;

constexpr int MAXN = 2020202;

constexpr ll P1 = 1000000007;
constexpr ll P2 = 1000000009;
constexpr ll M1 = 245;
constexpr ll M2 = 463;

ll pw(ll x, ll n, ll mod)
{
    ll res = 1;
    while(n) {
        if(n&1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

struct PowTable {
    vector<ll> pw1{1}, pw2{1}, ipw1{1}, ipw2{1};

    static ll mod_pow(ll x, ll n, ll mod) {
        ll res = 1;
        while (n) {
            if (n & 1) res = res * x % mod;
            x = x * x % mod;
            n >>= 1;
        }
        return res;
    }

    void ensure(int n) {
        if ((int)pw1.size() > n) return;

        int old = (int)pw1.size();
        pw1.resize(n+1); pw2.resize(n+1);
        ipw1.resize(n+1); ipw2.resize(n+1);

        static const ll invM1 = mod_pow(M1, P1-2, P1);
        static const ll invM2 = mod_pow(M2, P2-2, P2);

        for (int i = old; i <= n; i++) {
            pw1[i]  = pw1[i-1]  * M1    % P1;
            pw2[i]  = pw2[i-1]  * M2    % P2;
            ipw1[i] = ipw1[i-1] * invM1 % P1;
            ipw2[i] = ipw2[i-1] * invM2 % P2;
        }
    }

    static PowTable& inst() {
        static PowTable t;
        return t;
    }
};


struct Hasher {
    const string& s;
    vector<ll> H1, H2;

    Hasher(const string& _s) : s(_s) {
        int n = s.size();
        H1.resize(n+1);
        H2.resize(n+1);
        auto& T = PowTable::inst();
        for(int i = 0; i < n; i++) {
            H1[i+1] = (H1[i] + s[i] * T.pw1[i] % P1) % P1;
            H2[i+1] = (H2[i] + s[i] * T.pw2[i] % P2) % P2;
        }
    }

    pair<ll, ll> Q(int l, int r)
    {
        l++; r++;
        auto& T = PowTable::inst();
        ll h1 = (H1[r] - H1[l-1] + P1) % P1 * T.ipw1[l-1] % P1;
        ll h2 = (H2[r] - H2[l-1] + P2) % P2 * T.ipw2[l-1] % P2;
        return pair(h1, h2);
    }
};

struct chash {
    size_t operator()(const pair<ll, ll>& x) const {
        return x.first * 1000003LL ^ x.second;
    }
};

vector<int> getP(const string& s)
{
    int n = s.size();
    int r, c;
    r = c = -1;
    vector<int> p(n);
    for(int i = 0; i < n; i++) {
        if(r >= i) p[i] = min(r-i, p[c*2-i]);
        else p[i] = 0;
        while(i-p[i]-1 >= 0 && i+p[i]+1 < n && s[i-p[i]-1] == s[i+p[i]+1]) p[i]++;
        if(i+p[i] > r) {
            r = i + p[i];
            c = i;
        }
    }
    return p;
}

void padding(string& s)
{
    string t; t.reserve(2*s.size()+1);
    t += '#';
    for(auto c : s) {
        t += c;
        t += '#';
    }
    s = t;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    auto& T = PowTable::inst();
    T.ensure(MAXN);
    int n;
    cin >> n;
    gp_hash_table<pair<ll, ll>, pair<int, int>, chash> cnt;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        padding(s);
        Hasher hs(s);
        int n = s.size();
        int r, c;
        r = c = -1;
        vector<int> p(n);
        gp_hash_table<pair<ll, ll>, int, chash> chk;
        for(int i = 0; i < n; i++) {
            if(r >= i) p[i] = min(r-i, p[c*2-i]);
            else p[i] = 0;
            while(i-p[i]-1 >= 0 && i+p[i]+1 < n && s[i-p[i]-1] == s[i+p[i]+1]) {
                p[i]++;
                if(!chk[hs.Q(i-p[i], i+p[i])]) {
                    chk[hs.Q(i-p[i], i+p[i])]++;
                    cnt[hs.Q(i-p[i], i+p[i])].first++;
                    cnt[hs.Q(i-p[i], i+p[i])].second = p[i];
                }
            }
            if(i+p[i] > r) {
                r = i + p[i];
                c = i;
            }
        }
    }
    int ans = 0;
    for(auto [i, j] : cnt) {
        if(j.first == n) {
            ans = max(ans, j.second);
        }
    }
    cout << ans << "\n";
}