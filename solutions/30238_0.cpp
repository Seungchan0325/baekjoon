#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 200005;

ll A[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll T;
    cin >> T;
    while(T--) {
        ll N;
        cin >> N;
        for(ll i = 1; i <= N; i++) {
            cin >> A[i];
        }

        ll ans = 0;
        ll even = 0;
        for(ll i = N; i >= 1; i--) {
            if(i&1) {
                if(A[i] > 0) {
                    ans += A[i] + even;
                    even = 0;
                }
            } else {
                if(A[i] > 0) {
                    even += A[i];
                } else {
                    ans += even;
                    even = 0;
                }
            }
        }

        if(even > 0) {
            ans = max({ans, ans + A[1] + even, ans + even - A[2]});
        }

        cout << ans << "\n";
    }
}