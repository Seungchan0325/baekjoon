#include <iostream>

using namespace std;

using ll = long long;

int main() {
    ll n, k; cin>>n>>k;
    
    ll lo = 1, hi = n * n;
    while(lo <= hi) {
        ll mid = (lo + hi) / 2;
        
        ll count = 0;
        for(ll i=1; i<=n; i++) 
            count += min<ll>(n, mid / i);
        
        if(count < k) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    cout<<lo;
}