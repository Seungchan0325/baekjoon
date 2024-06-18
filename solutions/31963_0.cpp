#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 250005;

ll N, Q, A[MAXN], D[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(ll i = 1; i <= N; i++) {
        cin >> A[i];
    }

    for(ll i = 2; i <= N; i++) {
        ll now = A[i];

        while(A[i-1] > now) {
            now *= 2;
            D[i]++;
        }

        now = A[i-1];
        while(2*now <= A[i]) {
            now *= 2;
            D[i]--;
        }
    }

    ll sum = 0;
    ll ans = 0;
    for(ll i = 1; i <= N; i++) {
        sum += D[i];
        sum = max(0LL, sum);
        ans += sum;
    }

    cout << ans;
}