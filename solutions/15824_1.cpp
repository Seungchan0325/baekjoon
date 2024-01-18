#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD = 1000000007LL;
const int MAXN = 3005;

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

    ll ans = 0;
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++) {
            ans += ((arr[j] - arr[i]) * square[j-i-1]) % MOD;
            ans %= MOD;
        }

    cout<<ans;
}