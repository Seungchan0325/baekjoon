#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;

int N, T;
ll h[MAXN];

int main()
{
    cin >> N >> T;
    for(int i = 0; i < N; i++) cin >> h[i];

    T /= 2;

    ll ans = 0;
    ll s = 0;
    for(int i = 1; i < N && i <= T; i++) {
        ll cand = s + ((T-i+1)/2) * (h[i] + h[i-1]);
        cand *= 2;
        if((T-i)%2 == 0) cand += h[i];
        else cand -= h[i-1];
        ans = max(ans, cand);
        s += h[i];
    }
    cout << ans;
}