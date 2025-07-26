
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;

const ll mod = 998244353;
const int MAXN = 24;

struct VectorHasher {
    size_t operator()(const std::array<char, MAXN>& v) const {
        size_t hash = v.size();
        for (char i : v) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

ll inv[130];
gp_hash_table<array<char, MAXN>, ll, VectorHasher> cache[MAXN][MAXN];

ll pw(ll x, ll n)
{
    ll ans = 1;
    while(n) {
        if(n&1) ans = ans * x % mod;
        x = x * x % mod;
        n>>=1;
    }
    return ans;
}

ll dp(int n, int y, array<char, MAXN>& s)
{
    if(y == 0) return 1;
    if(n < y) return 0;
    
    int p0 = s[0];
    int pnp2 = s[n+2];
    s[0] = 0;
    s[n+1] += s[n+2];
    s[n+2] = 0;

    if(auto it = cache[n][y].find(s); it != cache[n][y].end()) {
        s[0] = p0;
        s[n+1] -= pnp2;
        s[n+2] = pnp2;
        return it->second;
    }
    
    ll& ret = cache[n][y][s] = 0;
    int sum = 1;
    for(int i = 1; i <= n+1; i++) {
        sum += s[i];
        s[i]--; s[i-1]++;
        ret = (ret + (s[i]+1) * dp(n-1, y, s) % mod) % mod;
        s[i]++; s[i-1]--;
    }

    ret = (ret + dp(n-1, y-1, s)) % mod;
    ret = ret * inv[sum] % mod;
    
    s[0] = p0;
    s[n+1] -= pnp2;
    s[n+2] = pnp2;
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    for(int i = 1; i < 130; i++) inv[i] = pw(i, mod-2);
    
    int N, M, X, Y;
    cin >> N >> M >> X >> Y;
    
    array<char, MAXN> s = {};
    for(int i = 1; i <= M; i++) {
        int h; cin >> h;
        h = (h + X - 1) / X;
        if(h <= N) s[h]++;
        else s[N+1]++;
    }
    Y = (Y + X - 1) / X;

    ll ans = dp(N, Y, s);
    cout << ans << "\n";
}