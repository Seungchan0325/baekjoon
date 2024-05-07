#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1e6 + 5;

ll N, B, C, A[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> B >> C;
    for(ll i = 0; i < N; i++) cin >> A[i];

    if(C >= B) {
        ll ans = 0;
        for(ll i = 0; i < N; i++) ans += B * A[i];
        cout << ans;
        return 0;
    }
    
    ll ans = 0;
    for(ll i = 0; i < N; i++) {
        if(A[i+1] > A[i+2]) {
            ll d = min(A[i], A[i+1] - A[i+2]);
            ans += d * (B + C);
            A[i] -= d; A[i+1] -= d;

            d = min({A[i], A[i+1], A[i+2]});
            ans += d * (B + C + C);
            A[i] -= d; A[i+1] -= d; A[i+2] -= d;
        } else {
            ll d = min({A[i], A[i+1], A[i+2]});
            ans += d * (B + C + C);
            A[i] -= d; A[i+1] -= d; A[i+2] -= d;

            d = min(A[i], A[i+1]);
            ans += d * (B + C);
            A[i] -= d; A[i+1] -= d;
        }
        ans += A[i] * B;
    }

    cout << ans;
}