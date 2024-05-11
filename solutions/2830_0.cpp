#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int LOGN = 20;

int N, cnt[LOGN + 1];

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) {
        int A;
        cin >> A;
        for(int j = 0; j <= LOGN; j++) {
            cnt[j] += (A & 1) ? 1 : 0;
            A >>= 1;
        }
    }

    ll ans = 0;
    for(int i = 0; i <= LOGN; i++) {
        ans += (ll)cnt[i] * (ll)(N - cnt[i]) * (1LL << i);
    }
    cout << ans;
}