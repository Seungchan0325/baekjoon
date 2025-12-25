#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int inf = 1e9;

ll N, A, B, Y[2020], S[2020];

void solve100()
{
    map<ll, bool> cache[101][101] = {};
    auto dp = [&](auto self, int i, int groups, ll on)
    {
        if(i == 0) {
            if(groups < A || groups > B) return false;
            return true;
        }
        if(cache[i][groups].contains(on)) return cache[i][groups][on];
        bool &ret = cache[i][groups][on];
        for(int j = 0; j < i; j++) {
            ll sum = S[i] - S[j];
            if(sum&~on) continue;
            ret |= self(self, j, groups+1, on);
            if(ret) return ret;
        }
        return ret;
    };

    ll ans = 0;
    for(int i = 63; i >= 0; i--) {
        if(!dp(dp, N, 0, ans|((1LL<<i)-1))) ans |= 1LL<<i;
    }
    cout << ans << "\n";
}

void solve()
{
    map<ll, int> cache[2020] = {};
    auto dp = [&](auto self, int i, ll on) {
        if(i == 0) return 0;
        if(cache[i].contains(on)) return cache[i][on];
        int &ret = cache[i][on];
        ret = inf;
        for(int j = 0; j < i; j++) {
            ll sum = S[i] - S[j];
            if(sum&~on) continue;
            ret = min(ret, self(self, j, on)+1);
        }
        return ret;
    };
    
    ll ans = 0;
    for(int i = 63; i >= 0; i--) {
        if(dp(dp, N, ans|((1LL<<i)-1)) > B) ans |= 1LL<<i;
    }
    cout << ans << "\n";
}

int main()
{
    cin >> N >> A >> B;
    for(int i = 1; i <= N; i++) cin >> Y[i];
    for(int i = 1; i <= N; i++) S[i] = Y[i] + S[i-1];

    if(N <= 100) solve100();
    else solve();
}