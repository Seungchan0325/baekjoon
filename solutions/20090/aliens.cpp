#include "aliens.h"
#include <bits/stdc++.h>

#include "grader.cpp"

using namespace std;

using ll = long long;
using llll = __int128_t;

struct Line {
    ll a, b, idx;
    ll get(ll x) {
        return a * x + b;
    }
};

const int MAXN = 505050;
int N;
ll dp[MAXN], sz[MAXN], R[MAXN], C[MAXN];
deque<Line> dq;

struct Frac {
    ll up, dw;
    Frac() : up(0), dw(1) {}
    Frac(ll _up, ll _dw) : up(_up), dw(_dw) {
        if(dw < 0) up = -up, dw = -dw;
    }
    Frac(ll x) : up(x), dw(1) {}
    bool operator < (const Frac& rhs) const {
        return (llll)up * rhs.dw < (llll)rhs.up * dw;
    }
    
    bool operator <= (const Frac& rhs) const {
        return (llll)up * rhs.dw <= (llll)rhs.up * dw;
    }
};

Frac cross(Line a, Line b)
{
    return Frac((b.b - a.b), (a.a - b.a));
}

void insert(Line l)
{
    while(dq.size() >= 2 && cross(dq.end()[-1], l) < cross(dq.end()[-1], dq.end()[-2])) dq.pop_back();
    dq.push_back(l);
}

Line query(ll x)
{
    while(dq.size() >= 2 && cross(dq[0], dq[1]) <= x) dq.pop_front();
    return dq[0];
}

void run(ll lambda)
{
    dq.clear();
    for(int i = 1; i <= N; i++) {
        Line l;
        l.a = -2 * (C[i] - 1);
        l.b = dp[i-1] + (C[i] - 1) * (C[i] - 1);
        if(i > 1 && R[i-1] - C[i] + 1 > 0) l.b -= (R[i-1] - C[i] + 1) * (R[i-1] - C[i] + 1);
        l.idx = i-1;
        insert(l);
        dp[i] = query(R[i]).get(R[i]) + R[i] * R[i] + lambda;
        sz[i] = sz[query(R[i]).idx] + 1;
    }
}

long long take_photos(int n, int m, int k, std::vector<int> r, std::vector<int> c) {
    vector<pair<int, int>> p;
    for(int i = 0; i < n; i++) {
        if(r[i] < c[i]) swap(r[i], c[i]);
        p.emplace_back(r[i], c[i]);
    }
    sort(p.begin(), p.end(), [](pair<int, int> a, pair<int, int> b){
        if(a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });
    vector<pair<int, int>> area;
    for(auto [ri, ci] : p) {
        while(area.size() && area.back().second >= ci) area.pop_back();
        area.emplace_back(ri, ci);
    }
    N = area.size();
    for(int i = 0; i < N; i++) {
        R[i+1] = area[i].first;
        C[i+1] = area[i].second;
    }
    ll lo = 0;
    ll hi = 1e15;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        run(mid);
        if(sz[N] >= k) lo = mid;
        else hi = mid;
    }

    run(lo);
    return dp[N] - lo * k;
}
