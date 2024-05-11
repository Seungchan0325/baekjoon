#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll N, M, t[100005];

bool check(ll T)
{
    ll cnt = 0;
    for(ll i = 0; i < N; i++) {
        cnt += T / t[i];
    }

    return M <= cnt;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(ll i = 0; i < N; i++) {
        cin >> t[i];
    }

    if(N == 1) {
        cout << t[0] * M;
        return 0;
    }

    sort(t, t + N);

    ll lo = -1;
    ll hi = M*t[0] + 5;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(check(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi;
}