#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXQ = 1005;
const ll MOD = 1e9 + 7;

ll N, x0, a, b, Q, qry[MAXQ], L[MAXQ], R[MAXQ];
int s[MAXQ];

int main()
{
    cin >> N >> x0 >> a >> b;
    cin >> Q;
    for(int i = 1; i <= Q; i++) {
        cin >> qry[i];
        L[i] = 0;
        R[i] = 1e9 + 7;
    }

    while(true) {
        bool isdone = true;
        vector<pair<ll, int>> v;
        for(int i = 1; i <= Q; i++) {
            if(L[i] + 1 < R[i]) {
                isdone = false;
                v.emplace_back((L[i] + R[i]) / 2, i);
            }
        }
        if(isdone) break;
        sort(v.begin(), v.end());

        memset(s, 0, sizeof(s));

        ll x = x0;
        int idx = lower_bound(v.begin(), v.end(), make_pair(x, -1)) - v.begin();
        s[idx]++;
        for(int i = 1; i < N; i++) {
            x = (x * a + b) % MOD;
            idx = lower_bound(v.begin(), v.end(), make_pair(x, -1)) - v.begin();
            s[idx]++;
        }
        for(int i = 1; i < v.size(); i++) s[i] += s[i-1];

        for(int i = 0; i < v.size(); i++) {
            int idx = v[i].second;
            if(s[i] <= qry[idx]) {
                L[idx] = v[i].first;
            } else {
                R[idx] = v[i].first;
            }
        }
    }

    ll ans = 0;
    for(int i = 1; i <= Q; i++) {
        ans += R[i];
    }
    cout << ans;
}