#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 200005;

struct Line {
    ll a, b;
    ll get(ll x)
    {
        return a * x + b;
    }
};

ll N, S[MAXN], P[MAXN], K[MAXN];

double cross(Line a, Line b)
{
    return (double)(a.b - b.b) / (b.a - a.a);
}

int main()
{
    cin >> N;
    for(ll i = 1; i <= N; i++) {
        cin >> S[i];
    }

    for(ll i = 1; i <= N; i++) {
        P[i] = P[i-1] + S[i];
        K[i] = K[i-1] + i * S[i];
    }

    // for(ll i = 1; i <= N; i++) {
    //     for(ll j = i; j <= N; j++) {
    //         cout << i << " " << j << " " << -i*P[j]+P[j]+K[j]+i*P[i-1]-P[i-1]-K[i-1] << "\n";
    //         prllf("a: %d b: %d\n", -i, i*P[i-1] - P[i-1] - K[i-1]);
    //     }
    // }

    ll ans = 0;

    vector<Line> v;
    for(ll i = 1; i <= N; i++) {
        Line l;
        l.a = -i;
        l.b = i * P[i-1] - P[i-1] - K[i-1];
        while(v.size() >= 2 && cross(v.end()[-1], v.end()[-2]) < cross(v.end()[-1], l)) {
            v.pop_back();
        }
        v.push_back(l);

        ll lo = -1;
        ll hi = v.size()-1;
        while(lo + 1 < hi) {
            ll mid = (lo + hi) / 2;
            if(cross(v[mid], v[mid+1]) >= P[i]) lo = mid;
            else hi = mid;
        }

        ans = max(ans, v[hi].get(P[i]) + P[i] + K[i]);
    }

    cout << ans;
}