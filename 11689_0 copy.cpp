#include <bits/stdc++.h>

using namespace std;

using ll = long long;

bool is_compsite[1000005];

int main()
{
    ll n;
    cin >> n;

    for(ll i = 2; i < 1e6; i++)
    {
        if(is_compsite[i]) continue;
        for(ll j = i + i; j < 1e6; j += i)
        {
            is_compsite[j] = true;
        }
    }
    
    ll remains = n;
    vector<ll> prime_factor;
    for(ll i = 2; i * i <= n; i++)
    {
        if(is_compsite[i] || remains % i != 0) continue;
        prime_factor.push_back(i);
        while(remains % i == 0) remains /= i;
    }
    if(remains != 1) prime_factor.push_back(remains);

    ll ans = 0;
    for(int taken = 1; taken < (1<<prime_factor.size()); taken++)
    {
        ll factor = 1;
        ll cnt = 0;
        for(int i = 0; i < prime_factor.size(); i++)
        {
            if(!(taken & (1<<i))) continue;
            factor *= prime_factor[i];
            cnt++;
        }
        if(cnt & 1)
            ans += n / factor;
        else
            ans -= n / factor;
    }
    cout << n - ans;
}