#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100005;

ll N, A[MAXN], B[MAXN], DP[MAXN];

struct Line {
    ll a, b;

    ll get(ll x) {
        return a * x + b;
    }
};

double cross(Line a, Line b) {
    return (double)(a.b - b.b) / (b.a - a.a);
}

int main()
{
    cin >> N;
    for(ll i = 1; i <= N; i++) cin >> A[i];
    for(ll i = 1; i <= N; i++) cin >> B[i];

    vector<Line> v;
    DP[1] = 0;
    v.push_back({B[1], 0});
    for(ll i = 2; i <= N; i++) {
        ll lo = 0;
        ll hi = v.size();
        while(lo + 1 < hi) {
            ll mid = (lo + hi) / 2;
            if(cross(v[mid], v[mid-1]) <= A[i]) lo = mid;
            else hi = mid;
        }
        DP[i] = v[lo].get(A[i]);
        Line l = {B[i], DP[i]};
        while(v.size() >= 2 && cross(v.end()[-1], v.end()[-2]) > cross(v.back(), l)) {
            v.pop_back();
        }
        v.push_back(l);
    }

    cout << DP[N];
}