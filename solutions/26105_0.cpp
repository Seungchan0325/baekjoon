#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 101010;

ll N, A[MAXN], S[MAXN], DP[MAXN];

int main()
{
    cin >> N;
    for(ll i = 1; i <= N; i++) cin >> A[i];
    for(ll i = 1; i <= N; i++) S[i] = S[i-1] + A[i];
    ll mn = 0;
    ll ans = 1e9;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
    for(ll i = 1; i <= N; i++) {
        mn += A[i];
        while(pq.size() && pq.top().first <= S[i]) mn = min(mn, S[i] - pq.top().second), pq.pop();
        DP[i] = mn;
        pq.emplace(S[i] + DP[i], S[i]);
        ans = min(ans, max(DP[i], S[N] - S[i]));
    }
    cout << ans;
}