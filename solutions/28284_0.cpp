#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 500005;

ll N, M, A[MAXN], B[2*MAXN];
pair<ll, ll> SE[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M;
    for(ll i = 1; i <= N; i++) {
        cin >> A[i];
    }
    sort(A + 1, A + N + 1);
    for(ll i = 1; i <= N; i++) {
        A[i] += A[i-1];
    }
    vector<ll> v;
    for(ll i = 0; i < M; i++) {
        cin >> SE[i].first >> SE[i].second;
        v.push_back(SE[i].first);
        v.push_back(SE[i].second + 1);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for(ll i = 0; i < M; i++) {
        ll s = lower_bound(v.begin(), v.end(), SE[i].first) - v.begin();
        ll e = upper_bound(v.begin(), v.end(), SE[i].second) - v.begin();
        B[s]++;
        B[e]--;
    }

    ll min_v = 0;
    ll max_v = 0;
    ll cnt = 0;
    for(ll i = 0; i < v.size() - 1; i++) {
        cnt += B[i];
        min_v += (v[i+1] - v[i]) * A[cnt];
        max_v += (v[i+1] - v[i]) * (A[N] - A[N-cnt]);
    }
    cout << min_v << " " << max_v;
}