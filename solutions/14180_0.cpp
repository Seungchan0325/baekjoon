#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 200005;

struct Line {
    ll a, b;
    ll get(ll x)
    {
        return a * x + b;
    }
};

double cross(Line a, Line b)
{
    return (double)(a.b - b.b) / (b.a - a.a);
}

ll N, A[MAXN];
ll S[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];

    ll ans = -1e18;
    ll p = 0;
    for(int i = 1; i <= N; i++) {
        p += A[i] * i;
        S[i] = S[i-1] + A[i];
    }

    vector<Line> v;
    for(int i = 1; i <= N; i++) {
        Line l;
        l.a = i;
        l.b = p - S[i-1];
        while(v.size() >= 2 && cross(v.end()[-1], v.end()[-2]) >= cross(v.end()[-1], l)) {
            v.pop_back();
        }
        v.push_back(l);

        int lo = -1;
        int hi = v.size()-1;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(cross(v[mid], v[mid+1]) < A[i]) lo = mid;
            else hi = mid;
        }

        ll cand = v[hi].get(A[i]) - i * A[i] + S[i] - A[i];
        ans = max(ans, cand);
    }

    v.clear();
    for(int i = N; i >= 1; i--) {
        Line l;
        l.a = i;
        l.b = p - S[i];
        while(v.size() >= 2 && cross(v.end()[-1], v.end()[-2]) <= cross(v.end()[-1], l)) {
            v.pop_back();
        }
        v.push_back(l);

        int lo = -1;
        int hi = v.size()-1;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(cross(v[mid], v[mid+1]) > A[i]) lo = mid;
            else hi = mid;
        }

        ll cand = v[hi].get(A[i]) + S[i] - i * A[i];
        ans = max(ans, cand);
    }
    cout << ans;
}