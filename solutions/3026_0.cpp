#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll RT = 316227;

bitset<10> on;
ll dp[2][12][RT];

bool test(ll x)
{
    while(x) {
        if(!on.test(x%10)) return false;
        x /= 10;
    }
    return true;
}

ll count_naive(ll x, ll n)
{
    ll cnt = 0;
    for(ll i = x; i <= n; i+=x) {
        cnt += test(i);
    }
    return cnt;
}

ll count_dp(ll x, ll n)
{
    ll ans = 0;
    memset(dp, -1, sizeof(dp));
    vector<int> nn(12);
    auto run = [&](auto self, int close, int idx, int mod) {
        if(idx == -1) return (ll)(mod == 0);

        ll& ret = dp[close][idx][mod];
        if(ret != -1) return ret;
        ret = 0;
        for(int i = 0; i < 10; i++) {
            if(on.test(i) && (!close || i <= nn[idx]))
                ret += self(self, close && i == nn[idx], idx-1, (mod*10+i)%x);
        }
        return ret;
    };
    for(int i = 0; i < 12; i++) {
        nn[i] = n % 10;
        n /= 10;
        for(int j = 1; j < 10; j++) {
            if(on.test(j) && (n != 0 || j <= nn[i]))
                ans += run(run, n == 0 && j == nn[i], i-1, j%x);
        }
    }
    return ans;
}

int main()
{
    ll X, A, B;
    cin >> X >> A >> B;
    string s; cin >> s;
    for(auto c : s) {
        on.set(c - '0');
    }

    if(X >= RT) {
        ll ans = count_naive(X, B) - count_naive(X, A-1);
        cout << ans << "\n";
    } else {
        ll ans = count_dp(X, B) - count_dp(X, A-1);
        cout << ans << "\n";
    }
}