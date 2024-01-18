#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD = 1000000007LL;
const int MAXN = 300005;

int n;
ll arr[MAXN], square[MAXN];

void calcSquare() {
    square[0] = 1;
    for(int i=1; i<MAXN; i++)
        square[i] = (square[i-1] * 2) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=0; i<n; i++) cin>>arr[i];

    sort(arr, arr + n);

    calcSquare();

    ll sum = 0, nsum = 0;
    for(int i=0; i<n; i++) {
        sum += (arr[i] * (square[i] - 1)) % MOD;
        sum %= MOD;
        nsum += (arr[i] * (square[n-i-1] - 1)) % MOD;
        nsum %= MOD;
    }

    ll ans = (sum - nsum + MOD) % MOD;

    cout<<ans;
}