#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 10005;

ll N, M, A[MAXN];

int main()
{
    cin >> N >> M;
    for(ll i = 0; i < N; i++) cin >> A[i];

    ll cnt = 0, sum = A[0];
    ll l = 0, r = 0;
    while(r < N) {
        if(sum < M) {
            sum += A[++r];
        } else if(sum > M) {
            sum -= A[l++];
        } else {
            cnt++;
            sum += A[++r];
        }
    }
    cout << cnt;
}