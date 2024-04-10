#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 300005;

int N;
vector<pair<int, int>> v;

ll f(ll x) {
    ll ret = 0;
    for(int i = 0; i < N; i++) {
        ret += abs(v[i].first - x) + abs(v[i].second - x);
    }
    return ret;
}

int main()
{
    cin >> N;
    v.resize(N);
    for(int i = 0; i < N; i++) {
        cin >> v[i].first;
    }
    for(int i = 0; i < N; i++) {
        cin >> v[i].second;
        v[i].first -= abs(N/2 - i);
        v[i].second -= abs(N/2 - i);
    }

    sort(v.begin(), v.end());

    ll lo = 0, hi = 1e12;
    while(hi - lo >= 3) {
        ll p = (lo*2 + hi)/3, q = (lo + hi*2)/3;
        if(f(p) <= f(q)) hi = q;
        else lo = p;
    }

    ll result = 1e18;
    for(int i = lo; i <= hi; i++) {
        result = min(f(i), result);
    }

    cout << result;
}