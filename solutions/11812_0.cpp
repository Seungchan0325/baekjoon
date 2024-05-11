#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    ll N, K, Q;
    cin >> N >> K >> Q;

    while(Q--) {
        ll u, v;
        cin >> u >> v;

        if(K == 1) {
            cout << abs(u - v) << "\n";
            continue;
        }

        ll ans = 0;

        while(u != v) {
            if(u < v) swap(u, v);
            ans++;
            u = (u + K - 2) / K;
        }
        cout << ans << "\n";
    }
}