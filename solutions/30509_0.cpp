#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100005;

ll N, L, R, S, M;
vector<pair<ll, ll>> uv;

bool check(ll k)
{
    ll m = M + R * (N - k);
    ll cnt = 0;
    priority_queue<ll> pq;
    for(auto [u, v] : uv) {
        if(u + v < S + m) {
            if(S < u) m += u - S;
            cnt++;
        } else if(u + v == S + m) {
            cnt++;
        } else {
            pq.push(u);
        }
    }

    while(!pq.empty()) {
        ll u = pq.top(); pq.pop();
        if(u < S) m += u - S;
        m -= L;
        if(m <= 0) break;
        cnt++;
    }
    return k <= cnt;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> L >> R;
    cin >> S >> M;
    for(ll i = 0; i < N; i++) {
        ll u, v;
        cin >> u >> v;
        uv.emplace_back(u, v);
    }
    sort(uv.begin(), uv.end(), [](pair<ll, ll> a, pair<ll, ll> b) {
        return a.first + a.second < b.first + b.second;
    });

    ll lo = 0, hi = N + 1;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(check(mid)) lo = mid;
        else hi = mid;
    }
    cout << lo;
}